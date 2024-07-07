#include "DBHandler.h"


DBHandler::DBHandler(const QSharedPointer<DBInterface> &db)
    : db(db)
{}

DBHandler::~DBHandler()
{
    db->close();
}

bool DBHandler::openDatabase()
{
    return db->open();
}

void DBHandler::closeDatabase()
{
    db->close();
}

bool DBHandler::insertTable(const QSharedPointer<TableManager>& table)
{
    tables.insert(table->getName(), table);
    QString query = table->createTable();
    return db->exec(query);
}

bool DBHandler::insertRow(const QString &tableName, const QVariantMap &data) const
{
    if (tables.contains(tableName))
    {
        QString query = tables[tableName]->insert(data);
        return db->exec(query);
    }
    return false;
}

bool DBHandler::updateRow(const QString &tableName, const QVariantMap &primaryKeys, const QVariantMap &data) const
{
    if (tables.contains(tableName))
    {
        QString query = tables[tableName]->update(primaryKeys, data);
        return db->exec(query);
    }
    return false;
}

bool DBHandler::removeRow(const QString &tableName, const QVariantMap &primaryKeys) const
{
    if (tables.contains(tableName))
    {
        QString query = tables[tableName]->remove(primaryKeys);
        return db->exec(query);
    }
    return false;
}

bool DBHandler::removeAllRows(const QString &tableName) const
{
    if (tables.contains(tableName))
    {
        QString query = tables[tableName]->removeAll();
        return db->exec(query);
    }
    return false;
}


