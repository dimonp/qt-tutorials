#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include <QWidget>
#include <QBasicTimer>

class RotateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RotateWidget(QWidget *parent = nullptr);

    void setLength(double length);
    void setSpeed(double speed);

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    QBasicTimer timer;

    double angle = 0;
    double length = 100;
    double speed = 5;
};

#endif // ROTATEWIDGET_H
