#include <QPainter>

#include "rotatewidget.h"

RotateWidget::RotateWidget(QWidget *parent)
    : QWidget{parent}
{
    timer.start(10, this);
    //setAttribute(Qt::WA_OpaquePaintEvent);
}

void RotateWidget::timerEvent(QTimerEvent *)
{
    angle += speed;
    repaint();
}

void RotateWidget::setSpeed(double speed)
{
    speed = speed;
}

void RotateWidget::setLength(double length)
{
    length = length;
}

void RotateWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(Qt::green, 10, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(pen);

    constexpr double radM = M_PI / 180;

    double x = qCos(angle * radM) * length;
    double y = qSin(angle * radM) * length;

    double centerX = geometry().width() / 2;
    double centerY = geometry().height() / 2;

    painter.drawLine(centerX, centerY, centerX + x, centerY + y);
}
