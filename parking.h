#ifndef PARKING_H
#define PARKING_H
#include<QString>
#include<QSqlQueryModel>
class Parking
{
public:
    Parking();
    Parking(int,int,QString,QString);
    int getid();
    int getdate();
    QString getnom();
    QString getprenom();
    void setid(int);
    void setdate(int);
    void setnom(QString);
    void setprenom(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
private :
    int id;
    int date;
    QString nom,prenom;

};

#endif // PARKING_H
