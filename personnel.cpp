#include "personnel.h"


personnel::personnel(int cin,QString nom,QString prenom,QString adresse,QDate date_n)
{
 this->cin=cin;
 this->nom=nom;
 this->prenom=prenom;
 this->adresse=adresse;
  this->date_n=date_n;


}
bool  personnel::ajouter()
{
QSqlQuery query;
QString res = QString::number(cin);

query.prepare("insert into personnel (cin, nom, prenom,adresse,date_n) values (:cin, :nom, :prenom, :adresse, :date_n)");

query.bindValue(":cin" ,res);
query.bindValue(":nom" ,nom);
query.bindValue(":prenom" ,prenom);
query.bindValue(":adresse" ,adresse);
query.bindValue(":date_n" ,date_n);
return query.exec();


}
QSqlQueryModel * personnel::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from personnel");

return model;


}
bool personnel::supprimer(int cin)

{
  QSqlQuery query;
   QString res = QString::number(cin);

   query.prepare("Delete from personnel where cin= :cin");

   query.bindValue(":cin",res);
return query.exec();
}

bool personnel::modifier(int cin)
{

       QSqlQuery query;
       QString cin_string=QString::number(cin);

    query.prepare("UPDATE personnel SET  adresse= :adresse , nom= :nom , prenom= :prenom  WHERE cin= :cin ");
    query.bindValue(":cin",cin);
    query.bindValue(":adresse",adresse);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);

    return query.exec();
     }

QSqlQueryModel * personnel:: rechercheNom(QString x)
    {
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from personnel where nom like '"+x+"%';");

    return model;
    }

QSqlQueryModel * personnel:: triernom()
    {
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from personnel ORDER BY nom,prenom");
        return model;
    }
