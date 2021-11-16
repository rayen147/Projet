#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"parking.h"
#include<QMessageBox>
#include<QIntValidator>
#include "connection.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  ui->le_matricule->setValidator(new QIntValidator(0, 9999999999, this));
  ui->le_periode->setValidator(new QIntValidator(0, 9999, this));
    ui->tab_parking->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Ajouter_clicked()
{ int matricule=ui->le_matricule->text().toInt();
  QString nom=ui->le_nom->text();
  QString prenom=ui->le_prenom->text();
  int periode=ui->le_periode->text().toInt();
  int prix=ui->le_prix->text().toInt();

 Parking P (matricule,nom,prenom,periode,prix);

 bool test=P.ajouter();
 ui->tab_parking->setModel(P.afficher());
 if(test){
     QMessageBox::information(nullptr, QObject::tr(""),
                 QObject::tr("ajout reussi\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
 }
 else{
     QMessageBox::critical(nullptr, QObject::tr(""),
                 QObject::tr("ajout non reussi\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);


 }
}

void MainWindow::on_pushButton_clicked()
{
Parking P1; P1.setmatricule(ui->le_matricule_supp->text().toInt());
bool test=P1.supprimer(P1.getmatricule());
QMessageBox msgBox;
if(test)
{
    msgBox.setText("Suppression avec succes.");
    ui->tab_parking->setModel(P1.afficher());}
else
    msgBox.setText("Echec de suppression");
    msgBox.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    int matricule=ui->ln_matricule->text().toInt();
    QString nom=ui->ln_nom->text();
      QString prenom=ui->ln_prenom->text();
      int periode=ui->ln_periode->text().toInt();
      int prix=ui->ln_prix->text().toInt();


      Parking P(matricule,nom,prenom,periode,prix);
      bool test=P.modifier();

         QMessageBox msgBox;
             if(test)

             {
                 msgBox.setText("modification avec succes");
             ui->tab_parking->setModel(P.afficher());
             }
             else

                 msgBox.setText(("echec de modification"));

                 msgBox.exec();
}

void MainWindow::on_pushButton_4_clicked()
{

    QSqlQueryModel* test=P.trier();
        QMessageBox msgBox;
            if(test){
                msgBox.setText("tri avec succes");
                ui->tab_parking->setModel(P.trier());
            }
                else
                msgBox.setText(("echec"));

                msgBox.exec();
}

void MainWindow::on_recherche_matricule_clicked()
{

        int matricule=ui->lr_matricule->text().toInt();
        QSqlQueryModel* test=P.rechercher_matricule(matricule);
        QMessageBox msgBox;
            if(test){
                msgBox.setText("recherche avec succes");
                ui->tab_parking->setModel(P.rechercher_matricule(matricule));
            }
                else
                msgBox.setText(("client introuvable"));

                msgBox.exec();
}
