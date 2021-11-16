#ifndef PARKING_H
#define PARKING_H
#include<QString>
#include<QSqlQueryModel>
class Parking
{
public:
    Parking();
    Parking(int,QString,QString,int,int);
    int getmatricule();
    QString getnom();
    QString getprenom();
    int getperiode();
    int getprix();
    void setmatricule(int);
    void setnom(QString);
    void setprenom(QString);
    void setperiode(int);
    void setprix(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* trier();
    QSqlQueryModel* rechercher_matricule(int matricule);
private :
    int matricule,periode,prix;
    QString nom,prenom;

};

#endif // PARKING_H
