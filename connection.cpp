#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test");//inserer le nom de la source de données ODBC
db.setUserName("aziz");//inserer nom de l'utilisateur
db.setPassword("aziz");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::errormessage(QString message){


    QMessageBox::critical(nullptr, "message",
                message, QMessageBox::Cancel);

}
void Connection::successmessage(QString message){

    QMessageBox::information(nullptr, "message",
                message, QMessageBox::Cancel);

}
