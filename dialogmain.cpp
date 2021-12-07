#include "dialogmain.h"
#include "ui_dialogmain.h"
#include "interfaceadmin.h"
#include "interfaceclient.h"
#include <QMessageBox>
Dialogmain::Dialogmain(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialogmain)
{
    ui->setupUi(this);
}

Dialogmain::~Dialogmain()
{
    delete ui;
}


void Dialogmain::on_btn_Login_clicked()
{
    QString nom = ui->lineEdit_nom->text();
    QString mdp = ui->lineEdit_mdp->text();
    bool test = p.login(nom,mdp);
    if(!test){
        QMessageBox::critical(nullptr, QObject::tr("Connexion"),
                    QObject::tr("Nom/Mot de passe est incorrecte.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if(test){
        p.setConnected(nom);
        QString role = p.getRole(nom);
        if (role =="Admin"){
           this->hide();
            Interfaceadmin interfaceadmin;
            interfaceadmin.show();

        }
        else if(role =="Client"){
            this->hide();
            Interfaceclient interfaceclient;
            interfaceclient.exec();
        }

    }
}

void Dialogmain::on_btn_Inscription_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Dialogmain::on_page_connexion_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Dialogmain::on_btn_mdpOublier_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void Dialogmain::on_page_connexion2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

