#ifndef ABONNEMENT_H
#define ABONNEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>


class Abonnement
{
public:
    Abonnement();
    Abonnement(int,QString,QString,int,int,int,int,QString);


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel * trier();
    QSqlQueryModel * trier2();
    QSqlQueryModel * trier3();

    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * notification();
    QSqlQueryModel * chercher(QString);

    QSqlQueryModel * trier_avance1(QString,QString);

private:
    QString nom,prenom,date_expiration;
    int Id,nombre_des_jeux,prix,duree,etat;




};




#endif // ABONNEMENT_H
