#include "parking.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Parking::Parking()
{
matricule=0;
nom=" ";
prenom=" ";
periode=0;
prix=0;
}

Parking::Parking(int matricule,QString nom,QString prenom,int periode,int prix)

{this->matricule=matricule; this->nom=nom; this->prenom=prenom;this->periode=periode;this->prix=prix;}
int Parking::getmatricule(){return matricule;}
QString Parking::getnom(){return nom;}
QString Parking::getprenom(){return prenom;}
int Parking::getperiode(){return periode;}
int Parking::getprix(){return prix;}
void Parking::setmatricule(int matricule){this->matricule=matricule;}
void Parking::setnom(QString nom){this->nom=nom;}
void Parking::setprenom(QString prenom){this->prenom=prenom;}
void Parking::setperiode(int periode){this->periode=periode;}
void Parking::setprix(int prix){this->prix=prix;}

bool Parking::ajouter()
{

    QSqlQuery query;
    QString matricule_string=QString::number(matricule);
     QString periode_string=QString::number(periode);
      QString prix_string=QString::number(matricule);
    query.prepare("INSERT INTO VOITURE (matricule,nom,prenom,periode,prix) "
                  "VALUES (:matricule, :nom ,:prenom,:periode,:prix)");
    query.bindValue(":matricule", matricule);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":periode", periode);
    query.bindValue(":prix", prix);
    return query.exec();
}
QSqlQueryModel* Parking::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
            model->setQuery("SELECT* FROM VOITURE");
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Periode"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));

                 return model;
}

bool Parking::modifier()
{
    QSqlQuery query;
    QString matricule_string=QString::number(matricule);
    QString periode_string=QString::number(periode);
    QString prix_string=QString::number(prix);
  query.prepare("UPDATE VOITURE SET  nom=:nom,prenom=:prenom,periode=:periode,prix=:prix WHERE matricule=:matricule ");
  query.bindValue(":matricule",matricule_string);
  query.bindValue(":nom", nom);
  query.bindValue(":prenom", prenom);
  query.bindValue(":periode", periode);
  query.bindValue(":prix", prix);
     query.exec();
}
bool Parking::supprimer(int matricule)
{ QSqlQuery query;
    query.prepare("Delete from VOITURE where matricule=:matricule ");
    query.bindValue(0, matricule);
    return query.exec();
}


QSqlQueryModel* Parking::trier()
{
QSqlQuery * q = new  QSqlQuery ();
                 QSqlQueryModel * model = new  QSqlQueryModel ();
                 q->prepare("SELECT * FROM VOITURE order by prix ASC");
                 q->exec();
                 model->setQuery(*q);
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("periode"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
                 return model;
}
QSqlQueryModel* Parking::rechercher_matricule(int matricule)
{

    QSqlQuery * q = new  QSqlQuery ();

                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("select * from VOITURE where matricule=:matricule");
                     q->bindValue(":matricule",matricule );
                     q->exec();

         model->setQuery(*q);
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("periode"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));


        return model;

}
