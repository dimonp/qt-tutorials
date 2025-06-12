#include <QFileDialog>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    ui->treeView->setModel(&sqliteModel);

    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::showItemDetails);
    connect(ui->treeView, &QTreeView::activated, this, &MainWindow::showItemDetails);
}

MainWindow::~MainWindow() = default;

void MainWindow::on_actionOpen_triggered() 
{
    QFileDialog openDialog(this);
    openDialog.setNameFilters({"Databases (*.db *.db3 *.sqlite *.sqlite3)", "Any files (*)"});
    if (openDialog.exec()) {
        QString dbFileName = openDialog.selectedFiles().first();
        sqliteModel.open(dbFileName);
    }
}

void MainWindow::showItemDetails(const QModelIndex &index)
{
    QString details = sqliteModel.getDetails(index);
    ui->textEdit->setText(details);
}