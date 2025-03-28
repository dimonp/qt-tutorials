#include "addressbook.h"
#include "adddialog.h"

#include "ui_addressbook.h"

AddressBook::AddressBook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AddressBook()) 
{
    ui->setupUi(this);
}

AddressBook::~AddressBook() = default;

void AddressBook::on_addButton_clicked() 
{
    AddDialog dialog(this);
    if (dialog.exec()) {
        QString name = dialog.getName();
        QString email = dialog.getEmail();

        if (!name.isEmpty() && !email.isEmpty()) {
            QListWidgetItem *item = new QListWidgetItem(name, ui->addressList);
            item->setData(Qt::UserRole, email);
            ui->addressList->setCurrentItem(item);
        }
    }   
}

void AddressBook::on_addressList_currentItemChanged() 
{
    QListWidgetItem *item = ui->addressList->currentItem();
    if (item) {
        ui->nameLabel->setText("Name:" + item->text());
        ui->emailLabel->setText("Email:" + item->data(Qt::UserRole).toString());
    } else {
        ui->nameLabel->setText("<No item selected>");
        ui->emailLabel->clear();
    }
}

void AddressBook::on_deleteButton_clicked() 
{
    QListWidgetItem* currentItem = ui->addressList->currentItem();
    
    if (currentItem) {
        int row = ui->addressList->row(currentItem);
        ui->addressList->takeItem(row);
        delete currentItem;

        if (ui->addressList->count() > 0) {
            ui->addressList->setCurrentRow(0);
        } else {
            on_addressList_currentItemChanged();
        }
    }
}
