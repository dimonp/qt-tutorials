#include <QQuickView>

class AddressBook : public QQuickView
{
    Q_OBJECT

public slots:
    void addButtonClicked();
    void addressListCurrentItemChanged();
    void deleteButtonClicked();

public:
    explicit AddressBook(QWindow *parent = nullptr);
    ~AddressBook();

};
