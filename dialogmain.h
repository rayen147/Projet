#ifndef DIALOGMAIN_H
#define DIALOGMAIN_H

#include <QDialog>
#include "personne.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Dialogmain; }
QT_END_NAMESPACE

class Dialogmain : public QDialog
{
    Q_OBJECT

public:
    Dialogmain(QWidget *parent = nullptr);
    ~Dialogmain();

private slots:
    void on_btn_Login_clicked();

    void on_btn_Inscription_clicked();

    void on_page_connexion_clicked();

    void on_btn_mdpOublier_clicked();

    void on_page_connexion2_clicked();


private:
    Ui::Dialogmain *ui;
    Personne p;
};
#endif // DIALOGMAIN_H
