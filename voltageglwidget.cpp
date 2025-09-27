// Modern OpenGL implementation using Qt wrappers
#include "voltageglwidget.h"
#include <QOpenGLFunctions>
#include <QVector2D>
#include <QVector4D>
#include <QPainter>
#include <QtMath>
#include <QWheelEvent>

// 顶点着色器源码：应用宽高比缩放并传递位置
static const char *vertexShaderSrc = R"(#version 330
layout(location = 0) in vec2 position;
uniform float u_aspect;
void main() {
    vec2 pos = position;
    pos.x *= u_aspect;
    gl_Position = vec4(pos, 0.0, 1.0);
}
 )";

// 片段着色器源码：使用统一颜色渲染
static const char *fragmentShaderSrc = R"(#version 330
out vec4 fragColor;
uniform vec4 u_color;
void main() {
    fragColor = u_color;
}
 )";

/**
 * @brief VoltageGLWidget构造函数
 * @param parent 父窗口指针，默认为nullptr
 *
 * 初始化OpenGL电压波形显示控件，设置最小宽度为400像素。
 */
VoltageGLWidget::VoltageGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setMinimumWidth(400);
}

/**
 * @brief VoltageGLWidget析构函数
 *
 * 清理OpenGL资源，包括VBO、VAO和着色器程序。
 */
VoltageGLWidget::~VoltageGLWidget()
{
    makeCurrent();
    vbo.destroy();
    vao.destroy();
    delete program;
    doneCurrent();
}

/**
 * @brief 接收电压和时间数据槽函数
 * @param voltages 电压值向量（单位：伏特）
 * @param times 时间戳向量（单位：微秒）
 *
 * 当接收到UDP数据时调用此函数，将电压和时间数据转换为毫秒时间戳并添加到样本缓冲区。
 * 限制缓冲区大小以防止内存过度使用，并触发重绘以更新波形显示。
 */
void VoltageGLWidget::onDataReceived(const QVector<double> &voltages, const QVector<double> &times)
{
    QMutexLocker locker(&mutex);
    // 添加传入的样本（时间戳单位为微秒，由 UdpReceiver 提供）
    int n = qMin(voltages.size(), times.size());
    if (n <= 0) return;

    qDebug() << "Received" << n << "samples, times range:" << times.first() << "to" << times.last();

    // 将传入的时间（微秒）转换为毫秒，并作为绝对时间戳添加
    for (int i = 0; i < n; ++i) {
        double tms = times[i] / 1000.0; // microsecond -> ms
        Sample s; s.timeMs = tms; s.volt = float(voltages[i]);
        sampleBuffer.append(s);
    }

    // 限制缓冲区大小以防止过度内存使用（保留最后 50000 个样本）
    const int maxBufferSize = 50000;
    if (sampleBuffer.size() > maxBufferSize) {
        sampleBuffer = sampleBuffer.mid(sampleBuffer.size() - maxBufferSize);
    }

    qDebug() << "Buffer size:" << sampleBuffer.size();

    // 顶点数据将在 paintGL 中从 sampleBuffer 重建以实现流式效果
    update();
}

/**
 * @brief 初始化OpenGL上下文
 *
 * 在OpenGL上下文首次创建时调用，编译和链接着色器程序，创建VBO和VAO，
 * 设置顶点属性，并初始化坐标轴VBO。检查着色器编译和链接错误。
 */
void VoltageGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    program = new QOpenGLShaderProgram(this);
    if (!program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSrc)) {
        qDebug() << "Vertex shader compilation failed:" << program->log();
    }
    if (!program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSrc)) {
        qDebug() << "Fragment shader compilation failed:" << program->log();
    }
    if (!program->link()) {
        qDebug() << "Shader program link failed:" << program->log();
    }

    vbo.create();
    vao.create();
    vao.bind();
    vbo.bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));
    vbo.release();
    vao.release();

    // 创建坐标轴 VBO：垂直轴在 x=-1（左侧），水平零电压在 y=0
    float axesVerts[] = {
        -0.98f, -1.0f,  // 垂直线底部（稍微内移以留出标签空间）
        -0.98f,  1.0f,  // 垂直线顶部
        -0.98f,  0.0f,  // 水平线左侧（原点）
         1.0f,   0.0f   // 水平线右侧
    };
    axesVbo.create();
    axesVbo.bind();
    axesVbo.allocate(axesVerts, sizeof(axesVerts));
    axesVertexCount = 4; // two lines (pairs)
    axesVbo.release();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/**
 * @brief 处理窗口大小变化
 * @param w 新的窗口宽度（像素）
 * @param h 新的窗口高度（像素）
 *
 * 当控件大小改变时调用，更新OpenGL视口以匹配新的尺寸。
 */
void VoltageGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

/**
 * @brief 处理鼠标滚轮事件
 * @param event 滚轮事件对象
 *
 * 根据修饰键缩放轴：Shift 缩放电压轴，Ctrl 缩放时间轴。
 */
void VoltageGLWidget::wheelEvent(QWheelEvent *event)
{
    QMutexLocker locker(&mutex);

    // 获取滚轮增量（通常为 ±120）
    int delta = event->angleDelta().y();
    if (delta == 0) return;

    // 缩放因子：向上滚放大，向下滚缩小
    double factor = (delta > 0) ? 0.9 : 1.1; // 缩小范围或窗口

    if (event->modifiers() & Qt::ShiftModifier) {
        // 缩放电压轴
        double centerV = (minV + maxV) / 2.0;
        double rangeV = maxV - minV;
        rangeV *= factor;
        minV = centerV - rangeV / 2.0;
        maxV = centerV + rangeV / 2.0;
        // 确保最小范围
        if (maxV - minV < 0.1) {
            minV = centerV - 0.05;
            maxV = centerV + 0.05;
        }
        qDebug() << "Voltage axis scaled: minV=" << minV << "maxV=" << maxV;
    } else if (event->modifiers() & Qt::ControlModifier) {
        // 缩放时间轴
        displayWindowMs *= factor;
        // 确保最小窗口
        if (displayWindowMs < 1.0) displayWindowMs = 1.0;
        if (displayWindowMs > 10000.0) displayWindowMs = 10000.0; // 最大10秒
        qDebug() << "Time axis scaled: displayWindowMs=" << displayWindowMs << "ms";
    }

    update(); // 触发重绘
    event->accept();
}

/**
 * @brief 渲染OpenGL场景
 *
 * 每次需要重绘时调用，清除缓冲区，从样本缓冲区重建顶点数据，
 * 应用子采样以限制顶点数量，然后使用GPU渲染波形和坐标轴。
 * 最后使用QPainter叠加绘制刻度和标签。
 */
void VoltageGLWidget::paintGL()
{
    QMutexLocker locker(&mutex);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!program)
        return;

    // 总是绘制坐标轴
    vao.bind();
    program->bind();

    float aspect = float(height() > 0 ? float(width()) / float(height()) : 1.0f);
    program->setUniformValue("u_aspect", aspect);

    // 使用灰色绘制坐标轴
    program->setUniformValue("u_color", QVector4D(0.6f, 0.6f, 0.6f, 1.0f));
    // 绑定坐标轴 VBO 并将其指向属性 0
    axesVbo.bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));
    glLineWidth(1.0f);
    glDrawArrays(GL_LINES, 0, axesVertexCount);
    axesVbo.release();

    // 如果有数据，绘制波形
    if (!sampleBuffer.isEmpty()) {
        // 从 sampleBuffer 重建当前显示窗口的顶点数据
        vertexData.clear();

        // 确定可见窗口：最新样本时间在最右；我们希望原点在左侧
        double latestTime = sampleBuffer.last().timeMs;
        double windowStart = latestTime - displayWindowMs;
        if (windowStart < 0) windowStart = 0;

        qDebug() << "Painting, buffer size:" << sampleBuffer.size() << "latestTime:" << latestTime;

        // 子采样以限制顶点数量（最大 10000 个顶点以提高性能）
        const int maxVertices = 10000;
        int totalSamples = sampleBuffer.size();
        int step = qMax(1, totalSamples / maxVertices);

        // 将样本时间 t 映射到归一化 x：xnorm = (t - windowStart) / displayWindowMs -> 0..1
        // 然后 NDC x = xnorm*2-1（左侧原点在 -1）
        for (int i = 0; i < totalSamples; i += step) {
            const Sample &s = sampleBuffer[i];
            // 最新样本的 xnorm=0（左侧）；较旧样本向右移动
            double age = latestTime - s.timeMs; // 0..displayWindowMs
            if (age < 0.0) continue;
            double xnorm = age / displayWindowMs; // 0..1
            if (xnorm < 0.0) continue;
            if (xnorm > 1.0) continue; // 超出窗口
            double nx = xnorm * 2.0 - 1.0; // 映射 0->-1（左侧），1->1（右侧）
            double clamped = qBound(minV, double(s.volt), maxV);
            double ny = (clamped - minV) / (maxV - minV) * 2.0 - 1.0;
            vertexData.append(float(nx));
            vertexData.append(float(ny));
        }

        qDebug() << "Vertex count:" << vertexData.size() / 2;

        if (!vbo.isCreated()) vbo.create();
        vbo.bind();
        vbo.allocate(vertexData.constData(), vertexData.size() * sizeof(float));
        vertexCount = vertexData.size() / 2;

        // 用绿色绘制波形
        program->setUniformValue("u_color", QVector4D(0.0f, 1.0f, 0.0f, 1.0f));
        glLineWidth(2.0f);
        if (vertexCount > 0) glDrawArrays(GL_LINE_STRIP, 0, vertexCount);

        // 恢复属性指针到波形 VBO（重新绑定）
        program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));
        vbo.release();
    }

    program->release();
    vao.release();

    // --- 使用 QPainter 叠加绘制刻度和标签（像素坐标）---
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(180,180,180)));
    QFont font = painter.font();
    font.setPointSize(9);
    painter.setFont(font);

    int w = width();
    int h = height();

    // 辅助函数：将 NDC 坐标 (nx, ny in -1..1) 转换为像素
    auto ndcToPixel = [&](float nx, float ny)->QPointF {
        float sx = (nx * aspect + 1.0f) * 0.5f * w;
        float sy = (1.0f - ny) * 0.5f * h;
        return QPointF(sx, sy);
    };

    // 时间刻度（底部轴）。使用 displayWindowMs (ms)
    double dur = qMax(displayWindowMs, 1.0);
    // 选择约 8 个刻度
    int targetTicks = 8;
    double rawStep = dur / targetTicks;
    // 良好的步长：1,2,5 * 10^k
    double magnitude = qPow(10.0, floor(log10(rawStep)));
    double residual = rawStep / magnitude;
    double niceStep;
    if (residual < 1.5) niceStep = 1.0 * magnitude;
    else if (residual < 3.5) niceStep = 2.0 * magnitude;
    else if (residual < 7.5) niceStep = 5.0 * magnitude;
    else niceStep = 10.0 * magnitude;

    // 绘制时间刻度：从左侧 0 到右侧 dur 的偏移
    for (double offset = 0.0; offset <= dur + 1e-6; offset += niceStep) {
        double xnorm = (offset / dur); // 0..1, 0 at left (newest)
        float nx = float(xnorm * 2.0 - 1.0);
        QPointF pt = ndcToPixel(nx, -1.0f);
        painter.drawLine(QPointF(pt.x(), h - 4), QPointF(pt.x(), h));
        QString label;
        if (niceStep >= 1000.0) {
            label = QString::number(offset/1000.0, 'g', 3) + "s";
        } else {
            label = QString::number(offset, 'g', 3) + "ms";
        }
        painter.drawText(QPointF(pt.x() + 2, h - 6), label);
    }

    // 沿左侧垂直轴的电压刻度，以 ny=0 为中心
    // 在 [minV, maxV] 上选择约 6 个刻度
    int vTicks = 6;
    double vrange = maxV - minV;
    double rawVStep = vrange / vTicks;
    double magV = qPow(10.0, floor(log10(rawVStep)));
    double resV = rawVStep / magV;
    double niceVStep;
    if (resV < 1.5) niceVStep = 1.0 * magV;
    else if (resV < 3.5) niceVStep = 2.0 * magV;
    else if (resV < 7.5) niceVStep = 5.0 * magV;
    else niceVStep = 10.0 * magV;

    double vstart = ceil(minV / niceVStep) * niceVStep;
    const float axisX = -0.98f; // 必须与 axesVbo 偏移匹配
    QFontMetrics fm(font);
    for (double v = vstart; v <= maxV + 1e-9; v += niceVStep) {
        double ny = (v - minV) / (maxV - minV) * 2.0 - 1.0; // -1..1
        QPointF pt = ndcToPixel(axisX, float(ny));
        // 在轴右侧绘制刻度
        painter.drawLine(QPointF(pt.x(), pt.y()), QPointF(pt.x() + 6, pt.y()));
        // 在轴左侧绘制标签（避免裁剪）
        QString lab = QString::number(v, 'g', 4);
        int tw = fm.horizontalAdvance(lab);
        painter.drawText(QPointF(pt.x() - tw - 6, pt.y() - 2), lab);
    }

    painter.end();
}
