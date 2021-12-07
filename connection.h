#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QApplication>

class Connection
{
public:
    Connection();
    bool createconnect();
    QSqlDatabase db;
    void errormessage(QString);
    void successmessage(QString);
};

#endif // CONNECTION_H
