#ifndef SERVICE_H
#define SERVICE_H
#include <QString>


class Service
{
public:
    Service();
    Service(QString,QString,QString,QString,QString,QString,QString);
private :
    QString etat_financial,produit,nom,description,raison_social,etablissement,date;
    QString getetat_financial();
    QString getproduit();
    QString getnom();
    QString getdescription();
    QString getraison_social();
    QString getetablissement();
    QString getdate();
    void setetat_financial(QString);
    void setproduit(QString);
    void setnom(QString);
    void setdescription(QString);
    void setraison_social(QString);
    void setetablissement(QString);
    void setdate(QString);
};

#endif // SERVICE_H
