#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "DBHandler.h"
#include "DBInterface.h"
#include "TableManager.h"

int main()
{
    QString driver      = "QSQLITE"; //"QPSQL";
    QString connection  = "conn1";
    QString dbPath      = "test.db3"; //"postgres";
    QString hostName    = "localhost";
    QString userName    = "postgres";
    QString password    = "postgres";
    quint16 port        = 5432;
    QSharedPointer<DBInterface> dbInterface = QSharedPointer<DBInterface>::create(driver, connection, hostName, dbPath, userName, password, port);

    DBHandler dbHandler(dbInterface);
    if (!dbHandler.openDatabase())
        return 1;

    QString tableName   = "USERS";
    QString userId      = "USER_ID";
    QString name        = "NAME";

    QSharedPointer<TableManager> usersTable = QSharedPointer<TableManager>::create(tableName);
    usersTable->addPrimaryKey(userId, ColumnType::INTEGER)
            .addColumn(name, ColumnType::TEXT);

    dbHandler.insertTable(usersTable);

    QVariantMap user;
    user[name] = "Kirill";
    dbHandler.insertRow(tableName, user);

    user[name] = "Andrei";
    dbHandler.insertRow(usersTable->getName(), user);

    QString orderId = "ORDER_ID";
    tableName       = "ORDERS";
    QString product = "PRODUCT";

    QSharedPointer<TableManager> ordersTable = QSharedPointer<TableManager>::create(tableName);
    ordersTable->addPrimaryKey(orderId, ColumnType::INTEGER)
               .addColumn(product, ColumnType::TEXT)
               .addForeignKey(userId, ColumnType::INTEGER, tableName, userId);

    dbHandler.insertTable(ordersTable);

    QVariantMap order;
    order[product] = "burger";
    order[userId] = 1;
    dbHandler.insertRow(ordersTable->getName(), order);

    order[product] = "chips";
    dbHandler.insertRow(ordersTable->getName(), order);
    return 0;
}
