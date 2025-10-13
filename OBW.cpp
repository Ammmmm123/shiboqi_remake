#include "OBW.h"

TestOpenGLWidget::TestOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void TestOpenGLWidget::initializeGL()
{
    // 1.初始化OpenGL函数，否则OpenGL函数不可调用
    initializeOpenGLFunctions();
}

void TestOpenGLWidget::resizeGL(int w, int h)
{

}

void TestOpenGLWidget::paintGL()
{
    // 2.initializeOpenGLFunctions();执行后，下面的函数才有执行的意义
    // 设置窗口颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}