#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

#include "TableManager.h"

class DBInterface
{
public:
    DBInterface(const QString &_driver, const QString &_connection, const QString &_hostName, const QString &_databaseName, const QString &_user, const QString &_password, quint16 _port);
    ~DBInterface();

    bool open();
    void close();

    bool exec(const QString& query);
    bool commit();

private:
    QSqlDatabase sdb;

    QString driver;
    QString connection;
    QString hostName;
    QString databaseName;
    QString user;
    QString password;
    quint16 port;

    QDir directory;
};

#endif // DBINTERFACE_H
