#ifndef PERSONNE_H
#define PERSONNE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class Personne
{
public:

    Personne();
    Personne(int,QString,QString,QString,QString,QString,int,int,int);
    int get_id(){return  id;}
    QString get_prenom(){return prenom;}
    QString get_email(){return email;}
    QString get_nom(){return nom;}
    QString get_mdp(){return mdp;}
    QString get_role(){return role;}
    int get_statuscompte(){return  statuscompte;}
    int get_statusverification(){return  statusverification;}
    int get_codeactivation(){return codeactivation;}
    bool login(QString,QString);
    void setConnected(QString);
    void disConnect();
    QString getRole(QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
private:
    int id,statuscompte,statusverification,codeactivation;
    QString email,nom,prenom,mdp,role;
};

#endif // PERSONNE_H
