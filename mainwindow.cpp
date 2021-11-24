#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"parking.h"
#include<QMessageBox>
#include<QIntValidator>
#include "connection.h"
#include "qcustomplot.h"
#include <QPlainTextEdit>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTcpServer>
#include<QTcpSocket>
#include"qrcode.h"
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  ui->le_matricule->setValidator(new QIntValidator(0, 9999999, this));
  ui->le_periode->setValidator(new QIntValidator(0, 9999, this));
    ui->tab_parking->setModel(P.afficher());
     popUp = new PopUp();
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
                msgBox.setText(("voiture introuvable"));

                msgBox.exec();
}

void MainWindow::on_pushButton_3_clicked()
{

    QSqlQueryModel* test=P.trier1();
        QMessageBox msgBox;
            if(test){
                msgBox.setText("tri avec succes");
                ui->tab_parking->setModel(P.trier1());
            }
                else
                msgBox.setText(("echec"));

                msgBox.exec();
}

void MainWindow::on_pushButton_5_clicked()
{

    QSqlQueryModel* test=P.trier2();
        QMessageBox msgBox;
            if(test){
                msgBox.setText("tri avec succes");
                ui->tab_parking->setModel(P.trier2());
            }
                else
                msgBox.setText(("echec"));

                msgBox.exec();
}

void MainWindow::on_recherche_nom_clicked()
{
    QString nom=ui->lr_nom->text();
    QSqlQueryModel* test=P.rechercher_nom(nom);
    QMessageBox msgBox;
        if(test){
            msgBox.setText("recherche avec succes");
            ui->tab_parking->setModel(P.rechercher_nom(nom));
        }
            else
            msgBox.setText(("voiture introubvable"));

            msgBox.exec();
}

void MainWindow::on_recherche_prenom_clicked()
{
    QString prenom=ui->lr_prenom->text();
    QSqlQueryModel* test=P.rechercher_prenom(prenom);
    QMessageBox msgBox;
        if(test){
            msgBox.setText("recherche avec succes");
            ui->tab_parking->setModel(P.rechercher_prenom(prenom));
        }
            else
            msgBox.setText(("voiture introubvable"));

            msgBox.exec();
}

void MainWindow::on_Ajouter_currentChanged(int index)
{
    // set dark background gradient:
                      QLinearGradient gradient(0, 0, 0, 400);
                      gradient.setColorAt(0, QColor(90, 90, 90));
                      gradient.setColorAt(0.38, QColor(105, 105, 105));
                      gradient.setColorAt(1, QColor(70, 70, 70));
                      ui->plot->setBackground(QBrush(gradient));


                      // create empty bar chart objects:
                      QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
                      amande->setAntialiased(false);
                      amande->setStackingGap(1);
                       //set names and colors:
                      amande->setName("Repartition des capaciter selon station ");
                      amande->setPen(QPen(QColor(0, 168, 140).lighter(130)));
                      amande->setBrush(QColor(0, 168, 140));
                      // stack bars on top of each other:

                      // prepare x axis with country labels:
                      QVector<double> ticks;
                      QVector<QString> labels;
                      P.statistique(&ticks,&labels);

                      QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                      textTicker->addTicks(ticks, labels);
                      ui->plot->xAxis->setTicker(textTicker);
                      ui->plot->xAxis->setTickLabelRotation(60);
                      ui->plot->xAxis->setSubTicks(false);
                      ui->plot->xAxis->setTickLength(0, 4);
                      ui->plot->xAxis->setRange(0, 8);
                      ui->plot->xAxis->setBasePen(QPen(Qt::white));
                      ui->plot->xAxis->setTickPen(QPen(Qt::white));
                      ui->plot->xAxis->grid()->setVisible(true);
                      ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                      ui->plot->xAxis->setTickLabelColor(Qt::white);
                      ui->plot->xAxis->setLabelColor(Qt::white);

                      // prepare y axis:
                      ui->plot->yAxis->setRange(0,10);
                      ui->plot->yAxis->setPadding(5); // a bit more space to the left border
                      ui->plot->yAxis->setLabel("Statistiques");
                      ui->plot->yAxis->setBasePen(QPen(Qt::white));
                      ui->plot->yAxis->setTickPen(QPen(Qt::white));
                      ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
                      ui->plot->yAxis->grid()->setSubGridVisible(true);
                      ui->plot->yAxis->setTickLabelColor(Qt::white);
                      ui->plot->yAxis->setLabelColor(Qt::white);
                      ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                      ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                      // Add data:

                      QVector<double> PlaceData;
                      QSqlQuery q1("select PERIODE from VOITURE");
                      while (q1.next()) {
                                    int  nbr_fautee = q1.value(0).toInt();
                                    PlaceData<< nbr_fautee;
                                      }
                      amande->setData(ticks, PlaceData);
                      // setup legend:
                      ui->plot->legend->setVisible(true);
                      ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                      ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
                      ui->plot->legend->setBorderPen(Qt::NoPen);
                      QFont legendFont = font();
                      legendFont.setPointSize(5);//888//
                      ui->plot->legend->setFont(legendFont);
                      ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pb_qr_clicked()
{
    int tabeq=ui->tab_parking->currentIndex().row();
                   QVariant idd=ui->tab_parking->model()->data(ui->tab_parking->model()->index(tabeq,0));
                   QString matricule= idd.toString();
                   QSqlQuery qry;
                   qry.prepare("select * from VOITURE where matricule=:matricule");
                   qry.bindValue(":matricule",idd.toString());
                   qry.exec();
                   QString nom, prenom ,ide;
                   int prix,periode;
                   while(qry.next()){
                       nom=qry.value(1).toString();
                       prenom=qry.value(2).toString();

                   }
                   ide=QString(matricule);
                   ide="matricule: "+matricule+" nom: "+nom+" prenom: "+prenom+" prix: "+prix+" periode: "+periode;
                   QrCode qr = QrCode::encodeText(ide.toUtf8().constData(), QrCode::Ecc::HIGH);

                   // Read the black & white pixels
                   QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
                   for (int y = 0; y < qr.getSize(); y++) {
                       for (int x = 0; x < qr.getSize(); x++) {
                           int color = qr.getModule(x, y);  // 0 for white, 1 for black

                           // You need to modify this part
                           if(color==0)
                               im.setPixel(x, y,qRgb(254, 254, 254));
                           else
                               im.setPixel(x, y,qRgb(0, 0, 0));
                       }
                   }
                   im=im.scaled(200,200);
                   ui->qr_label1->setPixmap(QPixmap::fromImage(im));
                   int i=0 ;
                   for(i=0;i<100;i=i+0.1){
                       i++;
                       ui->progressBar->setValue(i);
                   }
}

void MainWindow::on_pb_notifier_clicked()
{
    popUp->setPopupText(ui->textEdit_notifier->toPlainText());

    popUp->show();
}
