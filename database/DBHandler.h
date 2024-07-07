#ifndef DBHANDLER_H
#define DBHANDLER_H

#include "DBInterface.h"
#include "TableManager.h"

#include <QString>
#include <QVector>
#include <QSharedPointer>
#include <QVariantMap>


class DBHandler
{
public:
    DBHandler(const QSharedPointer<DBInterface>& db);
    ~DBHandler();

    bool openDatabase();
    void closeDatabase();

    bool insertTable(const QSharedPointer<TableManager>& table);

    bool insertRow(const QString &tableName, const QVariantMap& data) const;
    bool updateRow(const QString &tableName, const QVariantMap& primaryKeys, const QVariantMap& data) const;
    bool removeRow(const QString &tableName, const QVariantMap& primaryKeys) const;
    bool removeAllRows(const QString &tableName) const;

private:
    QSharedPointer<DBInterface> db;
    QMap<QString, QSharedPointer<TableManager>> tables;
};

#endif // DBHANDLER_H
