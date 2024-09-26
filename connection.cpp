#include "connection.h"
#include <QTextCodec>

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test = false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("AssociationElwafa");
    db.setUserName("nihed");
    db.setPassword("esprit17");
    db.setConnectOptions("CONNECTOPTION=SQL_ATTR_PACKET_SIZE=8192;SQL_ATTR_CONNECTION_TIMEOUT=5;SQL_ATTR_LOGIN_TIMEOUT=5;SQL_ATTR_TRACEFILE=;");


    if (db.open())
        test = true;

    return test;
}
