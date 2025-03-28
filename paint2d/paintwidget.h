#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <random>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::default_random_engine randomEngine;
};

#endif // PAINTWIDGET_H
