#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    connect(ui->lengthSlider, &QSlider::valueChanged, [that = ui->rotateWidget](int value) {
        that->setLength(value);
    });

    connect(ui->speedSlider, &QSlider::valueChanged, [that = ui->rotateWidget](int value) {
        that->setSpeed(value);
    });

    ui->lengthSlider->setValue(100);
    ui->speedSlider->setValue(10);
}

MainWindow::~MainWindow() = default;
