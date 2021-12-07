#include "service.h"


Service::Service()
{


    etat_financial="";
    produit="";
    nom="";
   description="";
   raison_social="";
   etablissement="";
   date="";
}
Service::Service(QString etat_financial,QString produit,QString nom,QString description,QString raison_social,QString etablissement,QString date)
{ this->etat_financial=etat_financial;
    this->produit=produit;
    this->nom=nom;
    this->description=description;
    this->raison_social=raison_social;
    this->etablissement=etablissement;
    this->date=date;


}
QString Service::getetat_financial(){return etablissement;}
QString Service:: getproduit(){return produit;}
QString Service::getnom(){return nom;}
QString Service::getdescription(){return description;}
QString Service::getraison_social(){return raison_social;}
QString Service::getetablissement(){return etablissement;}
QString Service::getdate(){return date;}
void Service::setetat_financial(QString etat_financial){this->etat_financial=etat_financial;}
void Service::setproduit(QString produit){this->produit=produit;}
void Service::setnom(QString nom){this->nom=nom;}
void Service::setdescription(QString description){this->description=description;}
void Service::setraison_social(QString raison_social){this->raison_social=raison_social;}
void Service::setetablissement(QString etablissement){this->etablissement=etablissement;}
void Service::setdate(QString date){this->date=date;}

