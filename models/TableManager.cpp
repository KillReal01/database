#include "TableManager.h"

TableManager::TableManager(const QString &tableName)
    : tableName(tableName)
{}

TableManager::~TableManager()
{}

TableManager &TableManager::addColumn(const QString &name, ColumnType type)
{
    columns.append(Column{name, type, false, "", ""});
    return *this;
}

TableManager &TableManager::addPrimaryKey(const QString &name, ColumnType type)
{
    columns.append(Column{name, type, true, "", ""});
    primaryKeys.append(name);
    return *this;
}

TableManager &TableManager::addForeignKey(const QString &name,ColumnType type, const QString &foreignKeyTable, const QString &foreignKeyColumn)
{
    columns.append(Column{name, type, false, foreignKeyTable, foreignKeyColumn});
    return *this;
}

QString TableManager::insert(const QVariantMap &data) const
{
    QString insertQuery = "INSERT INTO " + tableName + " (";
    QStringList columnNames;
    QStringList placeholders;

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        QString key = it.key();
        QString value = it.value().toString();
        wrapText(key, value);
        columnNames.append(key);
        placeholders.append(value);
    }

    insertQuery += columnNames.join(", ") + ") VALUES (" + placeholders.join(", ") + ");";
    return insertQuery;
}

QString TableManager::update(const QVariantMap& primaryKeys, const QVariantMap &data) const
{
    QString updateQuery = "UPDATE " + tableName + " SET ";

    QStringList setClause;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        QString key = it.key();
        QString value = it.value().toString();
        wrapText(key, value);
        setClause.append(key + " = " + value);
    }
    updateQuery += setClause.join(", ");

    QStringList whereClause; 
    for (auto it = primaryKeys.begin(); it != primaryKeys.end(); ++it)
    {
        QString key = it.key();
        QString value = it.value().toString();
        wrapText(key, value);
        whereClause.append(key + " = " + value);
    }

    updateQuery += " WHERE " + whereClause.join(" AND ") + ";";
    return updateQuery;
}

QString TableManager::remove(const QVariantMap& primaryKeys) const
{
    QString deleteQuery = "DELETE FROM " + tableName + " WHERE ";

    QStringList whereClause;
    for (auto it = primaryKeys.begin(); it != primaryKeys.end(); ++it)
    {
        QString key = it.key();
        QString value = it.value().toString();
        wrapText(key, value);
        whereClause.append(key + " = " + value);
    }
    deleteQuery += whereClause.join(" AND ") + ";";
    return deleteQuery;
}

QString TableManager::removeAll() const
{
    QString deleteQuery = "DELETE FROM " + tableName + ";";
    return deleteQuery;
}

QString TableManager::createTable() const
{
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
    QStringList columnDefinitions;
    QStringList foreignKeyDefinitions;

    for (const Column& column : columns)
    {
        QString columnDef = column.name + " " + typeToString(column.type);
        if (column.isPrimaryKey && primaryKeys.size() == 1)
        {
            columnDef += " PRIMARY KEY";
        }
        columnDefinitions.append(columnDef);

        if (!column.foreignKeyTable.isEmpty() && !column.foreignKeyColumn.isEmpty())
        {
            QString foreignKeyDef = "FOREIGN KEY (" + column.name + ") REFERENCES " + column.foreignKeyTable + " (" + column.foreignKeyColumn + ")";
            foreignKeyDefinitions.append(foreignKeyDef);
        }
    }

    if (primaryKeys.size() > 1)
    {
        columnDefinitions.append("PRIMARY KEY (" + primaryKeys.join(", ") + ")");
    }

    createTableQuery += columnDefinitions.join(", ");
    if (!foreignKeyDefinitions.isEmpty())
    {
        createTableQuery += ", " + foreignKeyDefinitions.join(", ");
    }
    createTableQuery += ")";
    return createTableQuery;
}

QString TableManager::getName() const
{
    return tableName;
}

QString TableManager::typeToString(const ColumnType& type) const
{
    switch (type) {
        case ColumnType::INTEGER:   return "INTEGER";
        case ColumnType::REAL:      return "REAL";
        case ColumnType::TEXT:      return "TEXT";
        case ColumnType::BLOB:      return "BLOB";
        default: return "Unknown";
    }
}

void TableManager::wrapText(const QString& key, QString &value) const
{
    for (const auto& column : columns)
        if (column.name == key && column.type == ColumnType::TEXT)
            value = "'" + value + "'";
}

