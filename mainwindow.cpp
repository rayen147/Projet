#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include<QMessageBox>
#include "service.h"
#include <QSqlQueryModel>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>

#include "statistique.h"





#include <QRegExpValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QRegExpValidator *validator=new  QRegExpValidator([a-z],this);
//            ui->lineEdit->setValidator(new QRegExpValidator([a-z] , this));
//    ui->lineEdit->setInputMask("AAAAAAAA");
//    ui->lineEdit_2->setInputMask("NNNNNNNN");

    ui->lineEdit_3->setInputMask("AAAAAAAA");
    ui->lineEdit_4->setInputMask("NNNNNNNN");
    QVector<QColor> colors(4);
    QVector<double> value(4);

    colors[0]=Qt::blue;
    colors[1]=Qt::yellow;
    colors[2]=Qt::green;
    colors[3]=Qt::black;
    value[0]=3.4;
    value[1]=7.4;
    value[2]=4.8;
    value[3]=5.1;
ui->mohamed->setData(value,colors);

// fonction statistique
QLineSeries *series=new QLineSeries();
series->append(0,6);
series->append(2,4);
series->append(3,8);
series->append(7,4);
series->append(10,5);
*series<<QPointF(11,1)<<QPointF(13,3)<<QPointF(17,6)<<QPointF(18,3)<<QPointF(20,2);
QChart *chart=new QChart();
// chart->legend()->hide();
chart->addSeries(series);
chart->createDefaultAxes();
chart->setTitle("line chart exemple");
chart->legend()->setVisible(true);
chart->legend()->setAlignment(Qt::AlignBottom);

QChartView *chartview=new QChartView(chart);
chartview->setRenderHints(QPainter::Antialiasing);
chartview->setParent(ui->horizontalFrame);





}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}








void MainWindow::on_register_2_clicked()
{
    //retrieve data from input
    QString username=ui->lineEdit_3->text();
    QString password_admin=ui->lineEdit_4->text();
    QString email=ui->lineEdit_5->text();
   QString phone=ui->lineEdit_7->text();
    QString  cin=ui->lineEdit_6->text();
    QString gender=ui->radioButton->text();
    QString gender_2=ui->radioButton_2->text();
    QString date_naissance=ui->dateEdit->text();
    //run our insert querry ou enrigistrer les donnee dans sql
    QSqlQuery qry;

  qry.prepare("INSERT INTO admine (username,password_admin,email,phone,cin,gender,date_naissance)"
              "VALUES(:username,:password_admin,:email,:phone,:cin,:gender,:date_naissance)");
    qry.bindValue(":username",username);
    qry.bindValue(":password_admin",password_admin);
   qry.bindValue(":email",email);
   qry.bindValue(":phone",phone);
   qry.bindValue(":cin",cin);
   qry.bindValue(":gender",gender);
   qry.bindValue(":date_naissance",date_naissance);
   if(qry.exec())
   {
       QMessageBox::information(this,"Inserted","try to login");
       ui->stackedWidget->setCurrentIndex(0);
   }
   else
   {
        QMessageBox::critical(this,"Not inserted","data wasnt inserted");
   }
}

void MainWindow::on_pushButton_clicked()
{
    QString username=ui->lineEdit->text();
    QString password_admin=ui->lineEdit_2->text();
    QSqlQuery qry;
   if(qry.exec("select * from admine where username='"+username+"'and password_admin='"+password_admin+"'"))
   {
       int count=0;
       while(qry.next())
       {count++;

       }
       if(count==1)
       {
           QMessageBox::information(this,"Login","loading successfull");
           ui->stackedWidget->setCurrentIndex(2);
       }
       if(count<1)
       {QMessageBox::warning(this,"Login","username and password are incorrect try again");}

   }
}


void MainWindow::on_ajouter_clicked()
{QString nom=ui->lineEdit_12->text();
    QString produit=ui->lineEdit_11->text();
    QString etat_financiere=ui->lineEdit_10->text();
    QString raison_social=ui->lineEdit_9->text();
    QString etablissement=ui->lineEdit_8->text();
    QString description=ui->lineEdit_13->text();
    QSqlQuery qry;

  qry.prepare("INSERT INTO servi (nom,produit,etat_financiere,raison_social,etablissement,description)"
              "VALUES(:nom,:produit,:etat_financiere,:raison_social,:etablissement,:description)");
    qry.bindValue(":nom",nom);
    qry.bindValue(":produit",produit);
   qry.bindValue(":etat_financiere",etat_financiere);
   qry.bindValue(":raison_social",raison_social);
   qry.bindValue(":etablissement",etablissement);
   qry.bindValue(":description",description);
   if(qry.exec())
   {
       QMessageBox::information(this,"edit","service added successfully");
   }
   else
   {
       QMessageBox::warning(this,"error","error");
   }






}



void MainWindow::on_supprimer_clicked()
{
    QString nom=ui->lineEdit_14->text();
    QSqlQuery qry;
    qry.prepare("Delete from servi where nom='"+nom+"'");
            if(qry.exec())
            {
              QMessageBox::critical(this,"delete","deleted");
            }
            else
            {
                QMessageBox::critical(this,"error","not deleted");
            }
}


void MainWindow::on_afficher_clicked()
{
    QSqlQuery req;
    model=new QStandardItemModel(6,6);
    int row=0;
    req.exec("select nom,produit,etat_financiere,raison_social,etablissement,description from servi");
    while(req.next())
    {
        for(int i=0;i<6;i++)
        {
            QStandardItem *item=new QStandardItem(req.value(i).toString());   //i le nombre de colone;
            model->setItem(row,i,item);
        }
        row++;

    }

    model->setHeaderData(0,Qt::Horizontal,"nom");
    model->setHeaderData(1,Qt::Horizontal,"produit");//ecrire header of table
    model->setHeaderData(2,Qt::Horizontal,"etat_financiere");
    model->setHeaderData(3,Qt::Horizontal,"raison_social");
    model->setHeaderData(4,Qt::Horizontal,"etablissement");
    model->setHeaderData(5,Qt::Horizontal,"description");


    ui->tableView->setModel(model);
}



void MainWindow::on_modifier_clicked()
{
    QString nom=ui->lineEdit_15->text();
    QString produit=ui->lineEdit_16->text();
    QString etablissement=ui->lineEdit_17->text();
    QSqlQuery qry;
    qry.prepare("update servi set  nom='"+nom+"',produit='"+produit+"',etablissement='"+etablissement+"'where nom='"+nom+"' or produit='"+produit+"' or etablissement='"+etablissement+"' " );
    if(qry.exec())
    {

        QMessageBox::critical(this,"edit","updated");
    }
    else
    {
        QMessageBox::critical(this,"error"," not updated");

    }

}

void MainWindow::on_pushButton_3_clicked()
{
    QString nom=ui->lineEdit_18->text();
    QSqlQuery qry;
    qry.prepare("select * from servi where nom='"+nom+"'");
    if(qry.exec())
    {QSqlQueryModel * model=new QSqlQueryModel();


        model->setQuery(qry);
        ui->tableView_2->setModel(model);

    }
    else
    {
        QMessageBox::warning(this,"error","no information");
    }
}

void MainWindow::on_trie_clicked()
{
    QSqlQuery qry;
    qry.prepare("select * from servi ORDER BY nom");
    if(qry.exec())


    {
        QSqlQueryModel * model=new QSqlQueryModel();


                model->setQuery(qry);
                ui->tableView_2->setModel(model);

    }
    else {
        QMessageBox::warning(this,"error","no information");
    }
}

void MainWindow::on_mailling_clicked()
{
    QString link="https://accounts.google.com/";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_write_clicked()
{ QFile file("test.txt");
    if(!file.open(QIODevice::WriteOnly))
    {

                  QMessageBox::warning(this,"title","file not open");
  }
                  QTextStream out(&file);
                  QString text=ui->plainTextEdit->toPlainText();
                  out <<text;
                  file.flush();
                  file.close();

}

void MainWindow::on_read_clicked()
{
    QFile file("test.txt");
        if(!file.open(QIODevice::ReadOnly))
        {

                      QMessageBox::warning(this,"title","file not open");
      }
                      QTextStream in(&file);
                      QString text=in.readAll();
                      ui->plainTextEdit->setPlainText(text);

                      file.close();
}
