#include <QPushButton>
#include <QDebug>

#include "test_yamlsettings.h"
#include "../yamlsettings.h"

TestYamlSettings::TestYamlSettings(QObject *parent) : QObject(parent) {}

void TestYamlSettings::testcaseQStringEncode()
{
    const char* expected = "_TEST string_";

    YAML::Node node;
    node = QString(expected);

    QVERIFY(node.IsScalar());
    QCOMPARE(node.as<std::string>(), expected);
}

void TestYamlSettings::testcaseQStringDecode()
{
    const char* expected = "_TEST string_";

    YAML::Node node(expected);

    QCOMPARE(node.as<QString>(), QString(expected));
}

void TestYamlSettings::testcaseQListEncode() 
{
    std::vector<int> expected = {1, 2, 3, 4, 5};

    YAML::Node node;
    node = QList<int>(expected.begin(), expected.end());
    
    QVERIFY(node.IsSequence());
    auto actual = node.as<std::vector<int>>();
    QCOMPARE(actual.size(), expected.size());
    QCOMPARE(actual, expected);
}

void TestYamlSettings::testcaseQListDecode() 
{
    YAML::Node node = YAML::Load("sequence: [1, 2, 3, 4, 5]");

    QList<int> actual = node["sequence"].as<QList<int>>();

    auto expected = QList<int>{1, 2, 3, 4, 5};
    QCOMPARE(actual.size(), expected.size());
    QCOMPARE(actual, expected);
}

void TestYamlSettings::testcaseQMapEncode() 
{
    std::map<QString, int> expected {{"one", 1}, {"two", 2}, {"three", 3}};

    YAML::Node node;
    node = QMap<QString, int>(expected);

    QVERIFY(node.IsMap());
    auto actual = node.as<std::map<QString, int>>();
    QCOMPARE(actual.size(), expected.size());
    QCOMPARE(actual, expected);
}


void TestYamlSettings::testcaseQMapDecode()
{
    YAML::Node node = YAML::Load("mapping: {one: 1, two: 2, three: 3}");

    QMap<QString, int> actual = node["mapping"].as<QMap<QString, int>>();

    auto expected = QMap<QString, int> {{"one", 1}, {"two", 2}, {"three", 3}};
    QCOMPARE(actual.size(), expected.size());
    QCOMPARE(actual, expected);
}


void TestYamlSettings::testcaseQRectEncode()
{
    YAML::Node node;
    node = QVariant(QRect(1, 2, 3, 4));
    
    QVERIFY(node.IsScalar());
    QCOMPARE(node.as<std::string>(), "@Rect(1 2 3 4)");
}

void TestYamlSettings::testcaseQRectDecode()
{
    YAML::Node node = YAML::Load("geometry: \"@Rect(1 2 3 4)\"");

    QVariant actual = node["geometry"].as<QVariant>();

    QCOMPARE(actual.typeId(), QMetaType::QRect);
    QCOMPARE(actual.toRect(), QRect(1, 2, 3, 4));
}

void TestYamlSettings::testcaseQByteArrayEncode()
{
    YAML::Node node;
    node = QVariant(QByteArray("0123456789abcdef"));
    
    QVERIFY(node.IsScalar());
    QCOMPARE(node.as<std::string>(), "@ByteArray(30313233343536373839616263646566)");
}


void TestYamlSettings::testcaseQByteArrayDecode()
{
    YAML::Node node = YAML::Load("data: \"@ByteArray(30313233343536373839616263646566)\"");

    QVariant actual = node["data"].as<QVariant>();

    QCOMPARE(actual.typeId(), QMetaType::QByteArray);
    QCOMPARE(actual.toByteArray(), QByteArray("0123456789abcdef"));
}