#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_pushButtonXLeft_clicked()
{
    ui->openGLWidget->updateView(-5, 0);
}

void MainWindow::on_pushButtonXRight_clicked()
{
    ui->openGLWidget->updateView(5, 0);
}

void MainWindow::on_pushButtonYLeft_clicked()
{
    ui->openGLWidget->updateView(0, -5);
}

void MainWindow::on_pushButtonYRight_clicked()
{
    ui->openGLWidget->updateView(0, 5);
}