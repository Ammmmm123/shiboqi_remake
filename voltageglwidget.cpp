// Modern OpenGL implementation using Qt wrappers
#include "voltageglwidget.h"
#include <QOpenGLFunctions>
#include <QVector2D>

static const char *vertexShaderSrc = R"(#version 330
layout(location = 0) in vec2 position;
uniform float u_aspect;
void main() {
    vec2 pos = position;
    pos.x *= u_aspect;
    gl_Position = vec4(pos, 0.0, 1.0);
}
 )";

static const char *fragmentShaderSrc = R"(#version 330
out vec4 fragColor;
void main() {
    fragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
 )";

VoltageGLWidget::VoltageGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setMinimumWidth(400);
}

VoltageGLWidget::~VoltageGLWidget()
{
    makeCurrent();
    vbo.destroy();
    vao.destroy();
    delete program;
    doneCurrent();
}

void VoltageGLWidget::onDataReceived(const QVector<double> &voltages, const QVector<double> &times)
{
    QMutexLocker locker(&mutex);
    vertexData.clear();

    int n = qMin(voltages.size(), times.size());
    if (n <= 1) return;

    double t0 = times.first();
    double tN = times.last();
    durationMs = (tN - t0) * 1000.0;
    if (durationMs <= 0) durationMs = 1.0;

    // Build vertices in NDC (-1..1)
    for (int i = 0; i < n; ++i) {
        double x = (times[i] - t0) * 1000.0 / durationMs; // 0..1
        double nx = x * 2.0 - 1.0; // -1..1
        double v = voltages[i];
        double clamped = qBound(minV, v, maxV);
        double ny = (clamped - minV) / (maxV - minV) * 2.0 - 1.0; // -1..1
        vertexData.append(float(nx));
        vertexData.append(float(ny));
    }

    // upload to GPU if context is ready
    if (isValid() && context()) {
        makeCurrent();
        if (!vbo.isCreated()) vbo.create();
        vbo.bind();
        vbo.allocate(vertexData.constData(), vertexData.size() * sizeof(float));
        vertexCount = vertexData.size() / 2;
        vbo.release();
        doneCurrent();
    }

    update();
}

void VoltageGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSrc);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSrc);
    program->link();

    vbo.create();
    vao.create();
    vao.bind();
    vbo.bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));
    vbo.release();
    vao.release();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void VoltageGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void VoltageGLWidget::paintGL()
{
    QMutexLocker locker(&mutex);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (vertexData.isEmpty() || !program)
        return;

    if (!vbo.isCreated()) {
        vbo.create();
    }
    vbo.bind();
    vbo.allocate(vertexData.constData(), vertexData.size() * sizeof(float));

    vao.bind();
    program->bind();

    float aspect = float(height() > 0 ? float(width()) / float(height()) : 1.0f);
    program->setUniformValue("u_aspect", aspect);

    // draw line strip
    glLineWidth(2.0f);
    glDrawArrays(GL_LINE_STRIP, 0, vertexData.size() / 2);

    program->release();
    vao.release();
    vbo.release();
}
