#include "addressbook.h"

AddressBook::AddressBook(QWindow *parent)
    : QQuickView(parent)
{
}

AddressBook::~AddressBook() = default;

void AddressBook::addButtonClicked()
{
    qDebug() << "Add ...";
}

void AddressBook::addressListCurrentItemChanged()
{
    qDebug() << "Select ...";
}

void AddressBook::deleteButtonClicked()
{
    qDebug() << "Delete ...";
}
