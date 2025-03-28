#include "adddialog.h"

#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) 
    : QDialog(parent)
    , ui(new Ui::AddDialog())
{
    ui->setupUi(this);
}

AddDialog::~AddDialog() = default;

QString AddDialog::getEmail() const 
{
    return ui->emailEdit->text();
}

QString AddDialog::getName() const 
{
    return ui->nameEdit->text();
}