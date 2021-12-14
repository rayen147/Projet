#ifndef PARKING_H
#define PARKING_H
#include<QString>
#include<QSqlQueryModel>
class Parking
{
public:
    Parking();
    Parking(int,QString,QString,int,int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* trier();
    QSqlQueryModel* trier1();
    QSqlQueryModel* trier2();
    QSqlQueryModel* rechercher_matricule(int matricule);
    QSqlQueryModel* rechercher_nom(QString nom);
    QSqlQueryModel* rechercher_prenom(QString prenom);
    void statistique(QVector<double>* ticks,QVector<QString> *labels);

private :
    int matricule,periode,prix;
    QString nom,prenom;

};

#endif // PARKING_H
