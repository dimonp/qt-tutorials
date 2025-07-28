#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QDirIterator>
#include "addressbook.h"

int main(int argc, char *argv[]) 
{
    QGuiApplication app(argc, argv);

#ifdef Q_OS_ANDROID
    QQuickStyle::setStyle("Material");
#endif

#ifdef QT_DEBUG
    QDirIterator qrc(":", QDirIterator::Subdirectories);
    while(qrc.hasNext())
        qDebug() << qrc.next();
#endif

    QQmlApplicationEngine engine;
    QObject::connect(
    &engine,
    &QQmlApplicationEngine::objectCreationFailed,
    &app,
    []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);

    AddressBook addressBook; // Create an instance of main window
    engine.rootContext()->setContextProperty("view", &addressBook);

    const QUrl url("qrc:/addressbook/view/Addressbook.qml");
    engine.load(url);

    return app.exec();
}
