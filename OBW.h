#ifndef TESTOPENGLWIDGET_H
#define TESTOPENGLWIDGET_H
// 1.引入相关库
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

// 2.继承相关类
class TestOpenGLWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit TestOpenGLWidget(QWidget *parent = nullptr);

protected:
    // 3.重载相关虚函数
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

signals:

};

#endif // TESTOPENGLWIDGET_H