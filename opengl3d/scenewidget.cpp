#include <QMouseEvent>
#include <QMatrix4x4>

#include "scenewidget.h"

SceneWidget::SceneWidget(QWidget *parent)
    : QOpenGLWidget {parent}
    , isMousePressed {false}
{
}

void SceneWidget::timerEvent(QTimerEvent *)
{
    updateView(0.1, -0.1);
    update();
}

void SceneWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClearDepth(10.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); 

    timer.start(10, this);
}

void SceneWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);

    float aspectRatio = static_cast<float>(w) / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (aspectRatio >= 1.0)
        glOrtho(-2.0 * aspectRatio, 2.0 * aspectRatio, -2.0, 2.0, 5.0, -5.0);
    else
        glOrtho(-2.0, 2.0, -2.0 / aspectRatio, 2.0 / aspectRatio, 5.0, -5.0);
}

void SceneWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(view.constData());
    
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)

    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)

    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
    glColor3f(1.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(yellow)

    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(1.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(yellow)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(yellow)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
    glEnd();
}

void SceneWidget::mousePressEvent(QMouseEvent *event)
{
    mousePressPosition = event->position();
    isMousePressed = true;
}

void SceneWidget::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed = false;
}

void SceneWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!isMousePressed)
        return;

    QPointF diff = event->position() - mousePressPosition;
    updateView(diff.x() / 100, diff.y() / 100);
}

void SceneWidget::updateView(float diffYaw, float diffPitch)
{
    const QMatrix4x4 invRotateY = view.inverted();
    const QVector4D worldAxisY = invRotateY * QVector4D(0, 1, 0, 0);
    view.rotate(diffYaw, worldAxisY.x(), worldAxisY.y(), worldAxisY.z());
    
    const QMatrix4x4 invRotateX = view.inverted();
    const QVector4D worldAxisX = invRotateX * QVector4D(1, 0, 0, 0);
    view.rotate(diffPitch, worldAxisX.x(), worldAxisX.y(), worldAxisX.z());
}