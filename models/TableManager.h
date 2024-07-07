#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QVariantMap>
#include <QString>


enum ColumnType
{
    INTEGER,
    REAL,
    BLOB,
    TEXT
};

struct Column
{
    QString name;
    ColumnType type;
    bool isPrimaryKey;
    QString foreignKeyTable;
    QString foreignKeyColumn;
};


class TableManager
{
public:
    explicit TableManager(const QString &tableName);
    virtual ~TableManager();

    TableManager& addColumn(const QString &name, ColumnType type);
    TableManager& addPrimaryKey(const QString &name, ColumnType type);
    TableManager& addForeignKey(const QString &name, ColumnType type, const QString &foreignKeyTable, const QString &foreignKeyColumn);

    QString insert(const QVariantMap& data) const;
    QString update(const QVariantMap& primaryKeys, const QVariantMap& data) const;
    QString remove(const QVariantMap& primaryKeys) const;
    QString removeAll() const;
    QString createTable() const;

    QString getName() const;

protected:
    QString typeToString(const ColumnType& type) const;
    void wrapText(const QString& key, QString &value) const;

protected:
    QString tableName;
    QList<Column> columns;
    QStringList primaryKeys;
};

#endif // TABLEMANAGER_H
