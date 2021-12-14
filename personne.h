#ifndef PERSONNE_H
#define PERSONNE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class Personne
{
public:

    Personne();
    Personne(int,QString,QString,QString);
    bool ajouter();
    int nbrPerso();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherRecherche(int);
    QSqlQueryModel * afficherTri(int);
    bool supprimer(int);
    bool modifier(int);
private:
    int id;
    QString email,nom,prenom;
};

#endif // PERSONNE_H
