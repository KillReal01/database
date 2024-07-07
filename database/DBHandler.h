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
    DBHandler(const QString &_driver, const QString &_connection, const QString &_hostName, const QString &_databaseName, const QString &_user, const QString &_password, quint16 _port);
    ~DBHandler();

    void addTable(const QSharedPointer<TableManager>& table);

    bool insert(const QString &tableName, const QVariantMap& data) const;
    bool update(const QString &tableName, const QVariantMap& primaryKeys, const QVariantMap& data) const;
    bool remove(const QString &tableName, const QVariantMap& primaryKeys) const;
    bool removeAll(const QString &tableName) const;

private:
    QSharedPointer<DBInterface> db;
    QMap<QString, QSharedPointer<TableManager>> tables;
};

#endif // DBHANDLER_H
