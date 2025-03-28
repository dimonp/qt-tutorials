#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class AddDialog; }
QT_END_NAMESPACE

/**
 * @brief A dialog class for adding new entries to an address book.
 *
 * This class provides a user interface for inputting new contact information,
 * typically including a name and an email address. It inherits from QDialog
 * to create a modal dialog window.
 *
 * @param parent The parent widget of this dialog. 
 */
class AddDialog : public QDialog 
{
    Q_OBJECT
public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

    QString getEmail() const;
    QString getName() const;

private:
    std::unique_ptr<Ui::AddDialog> ui;
};