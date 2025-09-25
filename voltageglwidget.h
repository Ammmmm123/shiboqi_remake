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

private:
    QMutex mutex;
    QVector<float> vertexData; // interleaved x,y in NDC (-1..1)
    double minV = -5.0, maxV = 5.0;
    double durationMs = 100.0; // visible window (ms) - will be set from times

    // Modern GL objects
    QOpenGLShaderProgram *program = nullptr;
    QOpenGLBuffer vbo{QOpenGLBuffer::VertexBuffer};
    QOpenGLVertexArrayObject vao;
    int vertexCount = 0;
};

#endif // VOLTAGEGLWIDGET_H
