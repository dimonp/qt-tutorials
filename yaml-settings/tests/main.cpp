#include <QApplication>
#include <QTest>

#include "test_yamlsettings.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTest::qExec(new TestYamlSettings, argc, argv);

    return 0;
}

