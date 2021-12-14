#include "abonnement.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDate>


Abonnement::Abonnement()
{

    Id=0;
    nom="";
    prenom="";
    nombre_des_jeux=0;
    prix=0;
    duree=0;
    etat=0;
    date_expiration="";

}



Abonnement::Abonnement(int Id,QString nom,QString prenom ,int nombre_des_jeux,int prix,int duree,int etat,QString date_expiration)
{
      this->Id=Id;
      this->nom=nom;
      this->prenom=prenom;
      this->nombre_des_jeux= nombre_des_jeux;
      this->duree=duree;
      this->prix=prix;
      this->etat=etat;
      this->date_expiration=date_expiration;

}






bool Abonnement::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(Id);

    query.prepare("INSERT INTO ABONNEMENT (Id,nom,prenom,nombre_des_jeux,prix,duree,etat,date_expiration)"
                  "VALUES (:Id,:nom,:prenom,:nombre_des_jeux,:prix,:duree,:etat,:date_expiration) ");

    query.bindValue(":Id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":nombre_des_jeux",nombre_des_jeux);
    query.bindValue(":duree",duree);
    query.bindValue(":prix",prix);
    query.bindValue(":etat",etat);
    query.bindValue(":date_expiration",date_expiration);
    return    query.exec();
}

QSqlQueryModel * Abonnement::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from ABONNEMENT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre_des_jeux"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("duree"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("etat"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("date expiration"));


    return model;
}
QSqlQueryModel * Abonnement::trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from ABONNEMENT ORDER BY Id");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre_des_jeux"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("duree"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("etat"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("date expiration"));


    return model;
}


//****************************************************


bool Abonnement::supprimer(int ID)
{
    QSqlQuery query;

    QString res= QString::number(ID);

    query.prepare("Delete from ABONNEMENT where Id=:ID");
    query.bindValue(":ID", res);

    return    query.exec();
}




bool Abonnement::modifier(int Id )
{
    QSqlQuery query;
    QString res= QString::number(Id);
  // QString res2= QString::number(nom);

    query.prepare("update ABONNEMENT set nom=:nom,prenom=:prenom,nombre_des_jeux=:nombre_des_jeux,prix=:prix,duree=:duree,etat=:etat,date_expiration=:date_expiration where Id=:ID");
    query.bindValue(":ID",res);
   query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":nombre_des_jeux",nombre_des_jeux);
    query.bindValue(":prix",prix);
    query.bindValue(":duree", duree);
    query.bindValue(":etat",etat);
    query.bindValue(":date_expiration",date_expiration);
    return    query.exec();

}



//********************************rechercher*************************************************

QSqlQueryModel * Abonnement::rechercher(QString re)
{
 QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("SELECT * FROM ABONNEMENT WHERE Id='"+re+"' ; ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre_des_jeux"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("duree"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("etat"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("date expiration"));

    return model;
}



//*************************notification


QSqlQueryModel * Abonnement::notification()
{
   QDate date=QDate::currentDate();
   QString date3=date.toString("dd.MM.yyyy");
   //******faire une nouvelle date +7jours
   QString date2 = date.toString("dd.MM.yyyy");
   QString x=date2.mid(0,2);
   int nv=x.toInt();
   nv=nv+7;
   x=QString::number(nv);
   date2.remove(0,2);
   date2.insert(0,&x);
   //QDate date_exp= QDate::fromString(date2,"dd.MM.yyyy");

   QSqlQueryModel * model= new QSqlQueryModel();
//QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
model->setQuery("SELECT * FROM ABONNEMENT WHERE DATE_EXPIRATION BETWEEN 'date3' AND 'date2' ");
/*model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("nombre_des_jeux"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("duree"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("etat"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("date expiration")); */


   return model;
}


//*************************************************************************************


QSqlQueryModel * Abonnement::chercher(QString rech)
{
QSqlQueryModel * model6 = new QSqlQueryModel();
model6->setQuery("SELECT * FROM ABONNEMENT WHERE ID LIKE'%"+rech+"%' or NOM LIKE'%"+rech+"%' or PRENOM LIKE'%"+rech+"%' or NOMBRE_DES_JEUX LIKE'%"+rech+"%' or DUREE LIKE'%"+rech+"%' ");
return model6;
}


