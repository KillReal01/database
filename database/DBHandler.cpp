#include "DBHandler.h"


DBHandler::DBHandler(const QString &_driver, const QString &_connection, const QString &_hostName, const QString &_databaseName, const QString &_user, const QString &_password, quint16 _port)
{
    db = QSharedPointer<DBInterface>::create(_driver, _connection, _hostName, _databaseName, _user, _password, _port);
    db->open();
}

DBHandler::~DBHandler()
{
    db->close();
}

void DBHandler::addTable(const QSharedPointer<TableManager>& table)
{
    tables.insert(table->getName(), table);
    db->executeQuery(table->createTable());
}

bool DBHandler::insert(const QString &tableName, const QVariantMap &data) const
{
    if (tables.contains(tableName))
    {
        QString query = tables[tableName]->insert(data);
        return db->executeQuery(query);
    }
    return false;
}

bool DBHandler::update(const QString &tableName, const QVariantMap &primaryKeys, const QVariantMap &data) const
{
    if (tables.contains(tableName))
    {
        QString query = tables[tableName]->update(primaryKeys, data);
        return db->executeQuery(query);
    }
    return false;
}

bool DBHandler::remove(const QString &tableName, const QVariantMap &primaryKeys) const
{
    if (tables.contains(tableName))
    {
        QString query = tables[tableName]->remove(primaryKeys);
        return db->executeQuery(query);
    }
    return false;
}

bool DBHandler::removeAll(const QString &tableName) const
{
    if (tables.contains(tableName))
    {
        QString query = tables[tableName]->removeAll();
        return db->executeQuery(query);
    }
    return false;
}


