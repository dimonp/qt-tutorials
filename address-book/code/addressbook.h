#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AddressBook; }
QT_END_NAMESPACE

/**
 * @brief The AddressBook class represents the main window of the address book application.
 *
 * This class inherits from QMainWindow and provides the core functionality
 * for managing contacts in an address book, including adding, deleting,
 * and displaying contact information.
 *
 * @param parent The parent widget of this AddressBook window. 
 */
class AddressBook : public QMainWindow 
{
    Q_OBJECT

private slots:
    void on_addButton_clicked();
    void on_addressList_currentItemChanged();
    void on_deleteButton_clicked();

public:
    explicit AddressBook(QWidget *parent = nullptr);
    ~AddressBook();

private:
    std::unique_ptr<Ui::AddressBook> ui;
};