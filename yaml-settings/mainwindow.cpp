#include <QStyle>
#include <QSettings>
#include <QMessageBox>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() = default;

void MainWindow::showMessage(const QString &message) {
    ui->statusbar->showMessage(message);
}

QStringList MainWindow::getData() const {
    QStringList data;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        data.append(ui->listWidget->item(i)->text());
    }
    return data;
}

void MainWindow::setData(const QStringList &data) {
    ui->listWidget->addItems(data);
}

void MainWindow::on_actionOpen_triggered() {
    QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Open action ...");
    msgBox.exec();
}

void MainWindow::on_pushButtonAdd_clicked() {
    if (QString text = ui->lineEdit->text(); !text.isEmpty()) {
        ui->listWidget->addItem(text);
    }
}

void MainWindow::on_pushButtonDelete_clicked() {
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    for (QListWidgetItem *item : selectedItems) {
        delete item;
    }
}