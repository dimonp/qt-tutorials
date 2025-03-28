#ifndef OFFSCREENROTATEWIDGET_H
#define OFFSCREENROTATEWIDGET_H

#include <QWidget>
#include <QBasicTimer>

class OffscreenRotateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OffscreenRotateWidget(QWidget *parent = nullptr);

    void setLength(double length);
    void setSpeed(double speed);

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void resizeBackbuffer(const QSize &newSize);
    void renderToBackbuffer();

    QBasicTimer timer;
    std::unique_ptr<QPixmap> backBuffer;

    double angle_ = 0;
    double length_ = 100;
    double speed_ = 5;
};

#endif // OFFSCREENROTATEWIDGET_H
