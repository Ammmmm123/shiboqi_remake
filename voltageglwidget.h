#ifndef VOLTAGEGLWIDGET_H
#define VOLTAGEGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QVector>
#include <QMutex>

class VoltageGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit VoltageGLWidget(QWidget *parent = nullptr);
    ~VoltageGLWidget() override;

public slots:
    // 接收电压和时间向量并触发重绘
    void onDataReceived(const QVector<double> &voltages, const QVector<double> &times);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QMutex mutex;
    QVector<float> vertexData; // 交错的 x,y 坐标，在 NDC (-1..1) 空间
    double minV = -5.0, maxV = 5.0;
    double durationMs = 100.0; // 可见窗口 (ms) - 将从时间数据设置
    // 流式缓冲区：时间 (ms) 和电压的对
    struct Sample { double timeMs; float volt; };
    QVector<Sample> sampleBuffer;
    double displayWindowMs = 200.0; // 滑动窗口宽度，单位 ms

    // 现代 OpenGL 对象
    QOpenGLShaderProgram *program = nullptr;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLBuffer axesVbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;
    int vertexCount = 0;
    int axesVertexCount = 0;
};

#endif // VOLTAGEGLWIDGET_H
