#include "personne.h"

Personne::Personne()
{ 
    id = 0;
    nom ="";
    prenom = "";
    email ="";
    role = "" ;
    mdp="";
    codeactivation =0;
    statusverification = 0;
    statuscompte = 0 ;

}
Personne::Personne(int id,QString email,QString nom,QString prenom,QString mdp,QString role,int statuscompte,int statusverification,int codeactivation)
{
  this->id=id;
  this->email=email;
  this->nom=nom;
  this->prenom=prenom;
  this->mdp=mdp;
  this->role=role;
  this->statuscompte=statuscompte;
  this->statusverification=statusverification;
  this->codeactivation=codeactivation;
}

bool Personne::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO personne (ID, NOM, PRENOM,email,mdp,role,statuscompte,statusverification,codeactivation) "
                    "VALUES (:id, :nom, :prenom, :email, :mdp, :role, :statuscompte, :statusverification, :codeactivation)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":email", email);
query.bindValue(":mdp", mdp);
query.bindValue(":role", role);
query.bindValue(":codeactivation", codeactivation);
query.bindValue(":statusverification", statusverification);
query.bindValue(":statuscompte", statuscompte);

return    query.exec();
}

QSqlQueryModel * Personne::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from personne");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("CODEACTIVATION"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("STATUSVERIFICATION"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("STATUSCOMPTE"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("MDP"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("Role"));
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
bool Personne::modifier()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("update personne  ");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":email", email);
query.bindValue(":mdp", mdp);
query.bindValue(":role", role);
query.bindValue(":codeactivation", codeactivation);
query.bindValue(":statusverification", statusverification);
query.bindValue(":statuscompte", statuscompte);

return    query.exec();
}

bool Personne::login(QString nom,QString mdp)
{
    disConnect();
QSqlQuery query;
query.prepare("select * from personne where  nom=:nom  and mdp =:mdp");
query.bindValue(":nom",nom);
query.bindValue(":mdp",mdp);

if(query.exec()){
    if(query.next()){

    return true;
    }
    else {
        return false;
    }
}
else {
    return false;
}

}
void Personne::setConnected(QString nom){
    QSqlQuery query;
    query.prepare("update personne set connexion=1 where nom=:nom");
    query.bindValue(":nom",nom);
    query.exec();
}
void Personne::disConnect(){
    QSqlQuery query;
    query.prepare("update personne set connexion=0 where connexion=1");
    query.exec();
}

QString Personne::getRole(QString nom){
    QSqlQuery q;
    q.prepare("select role from personne where nom=:nom ");
    q.bindValue(":nom",nom);
    if(q.exec()){
        while(q.next()){
            QString role =q.boundValue(0).toString();
            return role;
        }
    }

}
