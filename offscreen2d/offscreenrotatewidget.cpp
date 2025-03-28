#include <QPainter>
#include <QResizeEvent>

#include "offscreenrotatewidget.h"

OffscreenRotateWidget::OffscreenRotateWidget(QWidget *parent)
    : QWidget{parent}
    , backBuffer(std::make_unique<QPixmap>(1, 1))
{
    timer.start(10, this);

    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_OpaquePaintEvent);
}

void OffscreenRotateWidget::setSpeed(double speed)
{
    speed_ = speed;
}

void OffscreenRotateWidget::setLength(double length)
{
    length_ = length;
}

void OffscreenRotateWidget::timerEvent(QTimerEvent *)
{
    angle_ += speed_;

    renderToBackbuffer();
    repaint();
}

void OffscreenRotateWidget::resizeEvent(QResizeEvent* event)
{
    resizeBackbuffer(event->size());
    QWidget::resizeEvent(event);
}

void OffscreenRotateWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *backBuffer);
}

void OffscreenRotateWidget::resizeBackbuffer(const QSize &newSize)
{
    backBuffer = std::make_unique<QPixmap>(newSize.width(), newSize.height());
}

void OffscreenRotateWidget::renderToBackbuffer()
{
    backBuffer->fill();

    QPainter painter(backBuffer.get());
    QPen pen(Qt::green, 10, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(pen);

    constexpr double radM = M_PI / 180;

    double x = qCos(angle_ * radM) * length_;
    double y = qSin(angle_ * radM) * length_;

    double centerX = geometry().width() / 2;
    double centerY = geometry().height() / 2;

    painter.drawLine(centerX - x, centerY - y, centerX + x, centerY + y);
}
