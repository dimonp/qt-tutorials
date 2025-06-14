#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    ui->treeView->setModel(&treeModel);
    ui->tableView->setModel(&tableModel);
}

MainWindow::~MainWindow() = default;
