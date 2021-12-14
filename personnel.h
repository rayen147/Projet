#ifndef PERSONNEL_H
#define PERSONNEL_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QDate>
#include <QSqlTableModel>

class personnel
{

public:
    personnel(){}
    personnel(int,QString,QString,QString,QDate);


    bool ajouter();
    QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier(int);
QSqlQueryModel* triernom();
QSqlQueryModel * rechercheNom(QString x);

private:
int cin;
QString nom, prenom,adresse;
QDate date_n;
};

#endif // PERSONNEL_H
