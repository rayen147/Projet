#include "parking.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Parking::Parking()
{
id=0;
date=0;
nom=" ";
prenom=" ";
}

Parking::Parking(int id,int date,QString nom,QString prenom)
{this->id=id; this->date=date; this->nom=nom; this->prenom=prenom;}
int Parking::getid(){return id;}
int Parking::getdate(){return date;}
QString Parking::getnom(){return nom;}
QString Parking::getprenom(){return prenom;}
void Parking::setid(int id){this->id=id;}
void Parking::setdate(int date){this->date=date;}
void Parking::setnom(QString nom){this->nom=nom;}
void Parking::setprenom(QString prenom){this->prenom=prenom;}
bool Parking::ajouter()
{bool test=false;

    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("INSERT INTO parking (id, forename, surname) "
                  "VALUES (:id, :forename, :surname)");
    query.bindValue(":id", id);
    query.bindValue(":forename", nom);
    query.bindValue(":surname", prenom);
    return query.exec();
}
bool Parking::supprimer(int id)
{ QSqlQuery query;
    query.prepare("Delete from parking where id=:id ");
    query.bindValue(0, id);
    return query.exec();
}
QSqlQueryModel* Parking::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
            model->setQuery("SELECT* FROM parking");
                 model->setHeaderData(0, Qt::Horizontal, QObject:: tr("ID Parking"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));}
