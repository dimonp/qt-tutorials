#include <QList>
#include <QMap>
#include <QRect>
#include <QDateTime>
#include <QStringDecoder>

#include "yamlsettings.h"
   
const QSettings::Format YamlSettings::format = 
    QSettings::registerFormat("yaml", YamlSettings::read, YamlSettings::write);

bool YamlSettings::read(QIODevice& device, QSettings::SettingsMap& settings) 
{
    QByteArray data = device.readAll();
    if (data.isEmpty()) {
        return false;
    }

    auto toUtf8 = QStringDecoder(QStringDecoder::Utf8);
    QString dataAsString = toUtf8(data);

    std::vector<YAML::Node> nodes = YAML::LoadAll(dataAsString.toStdString());
    for(auto it : nodes) {
        recursiveParse(it, QString(), settings);
    }
    
    return true;
}

bool YamlSettings::write(QIODevice& device, const QSettings::SettingsMap& settings) 
{
    YAML::Node rootNode(YAML::NodeType::Undefined);

    for (const auto& [key, value] : settings.asKeyValueRange()) {
        QStringList groups = key.split("/");

        YAML::Node currNode(rootNode);
        for (auto it = groups.cbegin(); it != groups.cend(); ++it) {
            currNode.reset(currNode[it->toStdString()]);
        }
        
        switch (value.metaType().id()) {
        case QMetaType::QStringList:
        case QMetaType::QVariantList:
            currNode = value.toStringList();
            currNode.SetStyle(YAML::EmitterStyle::Flow);
            break;

        case QMetaType::QVariantMap:
            currNode = value.toMap();
            currNode.SetStyle(YAML::EmitterStyle::Flow);
            break;
                
        default:
            currNode = value;
            break;
        }
    }

    std::stringstream out;
    out << rootNode;
    std::string cc = out.str();

    QTextStream qOut(&device);
    qOut << QString::fromStdString(cc);

    return qOut.status() == QTextStream::Ok;
}

void YamlSettings::recursiveParse(YAML::Node node, QString &&path, QSettings::SettingsMap &output)
{
    const char *delimeter = path.isEmpty() ? "" : "/";

    switch (node.Type()) {
    case YAML::NodeType::Null:
    case YAML::NodeType::Undefined:
        break;

    case YAML::NodeType::Scalar:
        output.insert(path, node.as<QVariant>());
        break;

    case YAML::NodeType::Sequence:
        output.insert(path, node.as<QStringList>());
        break;

    case YAML::NodeType::Map:
        for(YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
            recursiveParse(it->second, path + delimeter + it->first.as<QString>(), output);
        }
        break;
    }
}

