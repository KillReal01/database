#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "DBHandler.h"
#include "TableManager.h"

int main()
{
    QString driver      = "QSQLITE"; //"QPSQL";
    QString connection  = "conn1";
    QString dbName      = "Iridium.db3"; //"postgres";
    QString hostName    = "localhost";
    QString userName        = "postgres";
    QString password    = "postgres";
    quint16 port        = 5432;

    DBHandler db(driver, connection, hostName, dbName, userName, password, port);

    QString tableName   = "USERS";
    QString userId      = "USER_ID";
    QString name        = "NAME";

    QSharedPointer<TableManager> usersTable = QSharedPointer<TableManager>::create(tableName);
    usersTable->addPrimaryKey(userId, ColumnType::INTEGER)
            .addColumn(name, ColumnType::TEXT);

    db.addTable(usersTable);

    QVariantMap user;
    user[name] = "Kirill";
    db.insert(tableName, user);

    user[name] = "Andrei";
    db.insert(usersTable->getName(), user);

    QString orderId = "ORDER_ID";
    tableName       = "ORDERS";
    QString product = "PRODUCT";

    QSharedPointer<TableManager> ordersTable = QSharedPointer<TableManager>::create(tableName);
    ordersTable->addPrimaryKey(orderId, ColumnType::INTEGER)
               .addColumn(product, ColumnType::TEXT)
               .addForeignKey(userId, ColumnType::INTEGER, tableName, userId);

    db.addTable(ordersTable);

    QVariantMap order;
    order[product] = "burger";
    order[userId] = 1;
    db.insert(ordersTable->getName(), order);

    order[product] = "chips";
    db.insert(ordersTable->getName(), order);

    return 0;
}
