#include <QFileDialog>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    ui->treeView->setModel(&sqliteModel);
}

MainWindow::~MainWindow() = default;

void MainWindow::on_actionOpen_triggered() {
    QFileDialog openDialog(this);
    openDialog.setNameFilters({"Databases (*.db *.db3 *.sqlite *.sqlite3)", "Any files (*)"});
    if (openDialog.exec()) {
        QString dbName = openDialog.selectedFiles().first();
        sqliteModel.open(dbName);
    }
}
