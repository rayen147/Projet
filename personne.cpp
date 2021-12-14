#include "personne.h"

Personne::Personne()
{
    id = 0;
    nom ="";
    prenom = "";
    email ="";

}
Personne::Personne(int id,QString email,QString nom,QString prenom)
{
  this->id=id;
  this->email=email;
  this->nom=nom;
  this->prenom=prenom;

}


bool Personne:: ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO personne (ID, NOM, PRENOM,email) "
                    "VALUES (:id, :nom, :prenom, :email)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":email", email);


return    query.exec();
}

QSqlQueryModel * Personne::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from personne");
return model;

}
QSqlQueryModel * Personne::afficherRecherche(int id)
{QSqlQueryModel * model= new QSqlQueryModel();
QString res= QString::number(id);
model->setQuery("select * from personne where id = '"+ res +"' ");


    return model;
}
QSqlQueryModel * Personne::afficherTri(int index)
{QSqlQueryModel * model= new QSqlQueryModel();

    switch(index){
    case 0 :
        model->setQuery("SELECT * FROM PERSONNE ORDER BY ID ASC");
    case 1 :
    model->setQuery("select * from personne order by id asc");
        break;
    case 2 :
        model->setQuery("select * from personne order by id desc");
        break;
    case 3 :
        model->setQuery("select * from personne order by nom asc");
        break;
    case 4:
        model->setQuery("select * from personne order by nom desc");
        break;
    case 5 :
        model->setQuery("select * from personne order by email asc");
        break;
    case 6 :
        model->setQuery("select * from personne order by email desc");
        break;
    case 7 :
        model->setQuery("select * from personne order by prenom asc");
        break;
    case 8 :
        model->setQuery("select * from personne order by prenom desc");
        break;


    }



    return model;
}
bool Personne::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from personne where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}
bool Personne::modifier(int id)
{
QSqlQuery query;
query.prepare("update personne set nom=:nom,prenom=:prenom,email=:email where id=:id ");
query.bindValue(":id",id);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":email",email);

return    query.exec();
}
