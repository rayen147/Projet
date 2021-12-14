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

bool Parking::ajouter()
{

    QSqlQuery query;
    QString matricule_string=QString::number(matricule);
     QString periode_string=QString::number(periode);
      QString prix_string=QString::number(matricule);
    query.prepare("INSERT INTO parking (matricule,nom,prenom,periode,prix) "
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
            model->setQuery("SELECT* FROM parking");

                 return model;
}

bool Parking::modifier()
{
    QSqlQuery query;
    QString matricule_string=QString::number(matricule);
    QString periode_string=QString::number(periode);
    QString prix_string=QString::number(prix);
  query.prepare("UPDATE parking SET  nom=:nom,prenom=:prenom,periode=:periode,prix=:prix WHERE matricule=:matricule ");
  query.bindValue(":matricule",matricule_string);
  query.bindValue(":nom", nom);
  query.bindValue(":prenom", prenom);
  query.bindValue(":periode", periode);
  query.bindValue(":prix", prix);
     query.exec();
}
bool Parking::supprimer(int matricule)
{ QSqlQuery query;
    query.prepare("Delete from parking where matricule=:matricule ");
    query.bindValue(0, matricule);
    return query.exec();
}


QSqlQueryModel* Parking::trier()
{
QSqlQuery * q = new  QSqlQuery ();
                 QSqlQueryModel * model = new  QSqlQueryModel ();
                 q->prepare("SELECT * FROM parking order by prix ASC");
                 q->exec();
                 model->setQuery(*q);
                 return model;
}
QSqlQueryModel* Parking::rechercher_matricule(int matricule)
{

    QSqlQuery * q = new  QSqlQuery ();

                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("select * from parking where matricule=:matricule");
                     q->bindValue(":matricule",matricule );
                     q->exec();

         model->setQuery(*q);



        return model;

}


