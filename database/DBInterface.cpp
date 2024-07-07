#include "DBInterface.h"

DBInterface::DBInterface(const QString &_driver, const QString &_connection, const QString &_hostName, const QString &_databaseName, const QString &_user, const QString &_password, quint16 _port)
    : driver(_driver)
    , connection(_connection)
    , hostName(_hostName)
    , databaseName(_databaseName)
    , user(_user)
    , password(_password)
    , port(_port)
    , directory("db")
{}

DBInterface::~DBInterface()
{
    close();
}

bool DBInterface::exec(const QString &query)
{
    if (sdb.isOpen())
    {
        QSqlQuery q(sdb);
        if (q.exec(query))
        {
            return true;
        }
        qDebug() << "[DBInterface] Failed to execute query:" << q.lastQuery()
                 << "; Error: " << q.lastError();
    }
    return false;
}

bool DBInterface::commit()
{
    return sdb.commit();
}

bool DBInterface::open()
{
    QDir curruntPath(QDir::currentPath());
    QDir directoryPath      = curruntPath.filePath(directory.path());
    QString databasePath    = directoryPath.filePath(databaseName);

    if (!directoryPath.exists())
        directoryPath.mkdir(".");

    sdb = QSqlDatabase::addDatabase(driver, connection);
    sdb.setHostName(hostName);
    sdb.setDatabaseName(databasePath);
    sdb.setUserName(user);
    sdb.setPassword(password);
    sdb.setPort(port);

    if (!sdb.open())
    {
        qDebug() << "[DBInterface] Failed to connect to database:" << sdb.lastError();
        return false;
    }
    return true;
}

void DBInterface::close()
{
    if (sdb.isOpen())
        sdb.close();
}

