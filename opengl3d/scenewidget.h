#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QBasicTimer>
#include <QMatrix4x4>

class SceneWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit SceneWidget(QWidget *parent = nullptr);

    void updateView(float rotateX, float rotateY);
private:
    QBasicTimer timer;

    QMatrix4x4 view;

    QPointF mousePressPosition;
    bool isMousePressed;

    void timerEvent(QTimerEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // SCENEWIDGET_H
