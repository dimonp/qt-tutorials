#ifndef TEST_YAML_SETTINGS_H
#define TEST_YAML_SETTINGS_H

#include <QtTest>

class TestYamlSettings: public QObject
{
    Q_OBJECT
public:
    explicit TestYamlSettings(QObject *parent = nullptr);

private slots:

    void testcaseQStringEncode();
    void testcaseQStringDecode();
    void testcaseQListEncode();
    void testcaseQListDecode();
    void testcaseQMapEncode();
    void testcaseQMapDecode();
    void testcaseQRectEncode();
    void testcaseQRectDecode();
    void testcaseQByteArrayEncode();
    void testcaseQByteArrayDecode();
};

#endif // TEST_YAML_SETTINGS_H
