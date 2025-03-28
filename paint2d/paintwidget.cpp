#include <QPainter>
#include <random>

#include "paintwidget.h"

using namespace std;

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget{parent}
    , randomEngine(std::time(0))
{}

void PaintWidget::paintEvent(QPaintEvent *)
{
    uniform_int_distribution<std::mt19937::result_type> distPtX(0, geometry().width());
    uniform_int_distribution<std::mt19937::result_type> distPtY(0, geometry().height());

    QPainter painter(this);

    for (auto _ = 50; _--;) {
        painter.setPen(QColor(randomEngine()));
        painter.drawLine(distPtX(randomEngine), distPtY(randomEngine), distPtX(randomEngine), distPtY(randomEngine));
    }

    for (auto _ = 50; _--;) {
        painter.setPen(QColor(randomEngine()));
        painter.drawEllipse(distPtX(randomEngine), distPtY(randomEngine), distPtX(randomEngine), distPtY(randomEngine));
    }
}
