#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"parking.h"
#include<QMessageBox>
#include<QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_parking->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Ajouter_clicked()
{ int id=ui->label->text().toInt();
  QString nom=ui->label_9->text();
  QString prenom=ui->label_10->text();
 Parking P() ;
}

void MainWindow::on_pushButton_clicked()
{
Parking P1; P1.setid(ui->lineEdit_2->text().toInt());
bool test=P1.supprimer(P1.getid());
QMessageBox msgBox;
if(test)
    msgBox.setText("Suppression avec succes.");
else
    msgBox.setText("Echec de suppression");
    msgBox.exec();
}
