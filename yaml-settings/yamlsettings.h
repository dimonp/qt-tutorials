#ifndef YAML_SETTINGS_H
#define YAML_SETTINGS_H

#include <QIODevice>
#include <QSettings>
#include <QString>

#include <yaml-cpp/yaml.h>

namespace YAML {

template<>
struct convert<QString>
{
    static Node encode(const QString &rhs) 
    { 
        return Node(rhs.toStdString()); 
    }

    static bool decode(const Node &node, QString &rhs)
    {
        if (!node.IsScalar())
            return false;

        rhs = QString::fromStdString(node.Scalar());
        return true;
    }
};

template<typename T>
struct convert<QList<T> >
{
    static Node encode(const QList<T>& rhs)
    {
        Node node(NodeType::Sequence);
        for (T value : rhs) {
            node.push_back(value);
        }
        return node;
    }

    static bool decode(const Node& node, QList<T>& rhs)
    {
        if (!node.IsSequence())
            return false;

        rhs.clear();
        const_iterator it = node.begin();
        while (it != node.end()) {
            rhs.push_back(it->as<T>());
            ++it;
        }
        return true;
    }
};

template<typename Key, typename Value>
struct convert<QMap<Key, Value>>
{
    static Node encode(const QMap<Key, Value> &rhs)
    {
        Node node(NodeType::Map);
        auto it = rhs.constBegin();
        while (it != rhs.constEnd()) {
            node.force_insert(it.key(), it.value());
            ++it;
        }
        return node;
    }

    static bool decode(const Node &node, QMap<Key, Value> &rhs)
    {
        if (!node.IsMap())
            return false;

        rhs.clear();
        const_iterator it = node.begin();
        while (it != node.end()) {
            rhs[it->first.as<Key>()] = it->second.as<Value>();
            ++it;
        }
        return true;
    }
};

template<>
struct convert<QVariant>
{
    static Node encode(const QVariant &rhs) 
    {
        QString result;

        switch (rhs.metaType().id()) {
            case QMetaType::UnknownType:
                result = "@Invalid()";
                break;

            case QMetaType::QRect: {
                QRect r = qvariant_cast<QRect>(rhs);
                result = QString::asprintf("@Rect(%d %d %d %d)", r.x(), r.y(), r.width(), r.height());
                break;
            }
            case QMetaType::QSize: {
                QSize s = qvariant_cast<QSize>(rhs);
                result = QString::asprintf("@Size(%d %d)", s.width(), s.height());
                break;
            }
            case QMetaType::QPoint: {
                QPoint p = qvariant_cast<QPoint>(rhs);
                result = QString::asprintf("@Point(%d %d)", p.x(), p.y());
                break;
            }
            case QMetaType::QDateTime: {
                QDateTime dt = qvariant_cast<QDateTime>(rhs);
                result = QString("@DateTime(") + dt.toString(Qt::ISODate) + ')';
                break;
            }
            case QMetaType::QByteArray: {
                QByteArray a = rhs.toByteArray();
                result = QString("@ByteArray(") + a.toHex() + ')';
                break;
            }
            default:
                result = rhs.toString();
        }

        return Node(result); 
    }

    static bool decode(const Node &node, QVariant &rhs)
    {
        if (!node.IsScalar())
            return false;

        const QString s = QString::fromStdString(node.Scalar());
        if (s.startsWith(u'@') && s.endsWith(u')')) {
            if (s.startsWith("@DateTime(")) {
                auto dt = QDateTime::fromString(QStringView{s}.sliced(10).chopped(1), Qt::ISODate);
                rhs = QVariant(dt);
            } else if (s.startsWith("@Rect(")) {
                QStringList args = s.sliced(6).chopped(1).split(u' ');
                if (args.size() == 4) {
                    auto rect = QRect(args[0].toInt(), args[1].toInt(), args[2].toInt(), args[3].toInt());
                    rhs = QVariant(rect);
                }
            } else if (s.startsWith("@Size(")) {
                QStringList args = s.sliced(6).chopped(1).split(u' ');
                if (args.size() == 2)
                    rhs = QVariant(QSize(args[0].toInt(), args[1].toInt()));
            } else if (s.startsWith("@Point(")) {
                QStringList args = s.sliced(7).chopped(1).split(u' ');
                if (args.size() == 2)
                    rhs = QVariant(QPoint(args[0].toInt(), args[1].toInt()));
            } else if (s.startsWith("@ByteArray(")) {
                auto hexArray = QByteArray::fromHex(QStringView{s}.sliced(11).chopped(1).toUtf8());
                rhs = QVariant(hexArray);
            }
        } else {
            rhs = QVariant(s);
        }
    
        return true;
    }
};

} // end of namespace YAML
    
class YamlSettings 
{
public:
    static const QSettings::Format format;

    static bool read(QIODevice& device, QSettings::SettingsMap& map);
    static bool write(QIODevice& device, const QSettings::SettingsMap& map);
private:
    static void recursiveParse(YAML::Node node, QString &&path, QSettings::SettingsMap &output);
};

#endif // YAML_SETTINGS_H