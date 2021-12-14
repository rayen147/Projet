#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QDebug>
#include <QIntValidator>
#include <QMap>
#include "personne.h"
#include "personnel.h"
#include "parking.h"
#include "abonnement.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->nombreper->setValidator(new QIntValidator(0,9,this));
    ui->prix_2->setValidator(new QIntValidator(0,9999,this));
    ui->prix_3->setValidator(new QIntValidator(0,9999,this));
    ui->prix_4->setValidator(new QIntValidator(0,9999,this));
    ui->prix_5->setValidator(new QIntValidator(0,9999,this));
    ui->nombreper_2->setValidator(new QIntValidator(0,9,this));
    ui->nombreper_3->setValidator(new QIntValidator(0,9,this));
    ui->nombreper_4->setValidator(new QIntValidator(0,9,this));
    ui->nombreper_9->setValidator(new QIntValidator(0,9,this));
    ui->nombreper_10->setValidator(new QIntValidator(0,9,this));
    ui->pourcentage->setValidator(new QIntValidator(0,99,this));
    ui->pourcentage_3->setValidator(new QIntValidator(0,99,this));

Connection c;
c.createconnect();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Connection c;
    bool validation = true;
    QString nom,prenom,evenement,nombreper,prix;
    nom = ui->nom->text();
    prenom = ui->prenom->text();
    evenement = ui->evenement->text();
    nombreper = ui->nombreper->text();


    QString inputs[4]={nom,prenom,evenement,nombreper};
     for(int i = 0; i < 4; i++) {
         if(inputs[i].length() == 0 ){
             validation = false;
         }
     }
if(!nombreper.toInt()){
validation=false;
}
    if(validation){
    c.createconnect();
     QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery(c.db);
    QSqlQuery* qry1=new QSqlQuery(c.db);
    qry1->prepare("SELECT prix,pourcentage,minper,maxper FROM evenement e FULL JOIN offre o ON e.nom=o.nomeve WHERE e.nom='"+evenement +"'  ;");
    qry1->exec();
    modal->setQuery(*qry1);
    QVariant index_prix =modal->index(0,0).data();
    QVariant index_offre =modal->index(0,1).data();
    QString prix =index_prix.toString();
    if(!prix.length()){
        c.errormessage("evenement existe pas ");
    }
    else{
        int prix_final=index_prix.toInt()*nombreper.toInt();
        int minper=modal->index(0,2).data().toInt();
        int maxper=modal->index(0,3).data().toInt();
        if(nombreper.toInt() >= minper && nombreper.toInt()<= maxper){
            prix_final-=prix_final * index_offre.toInt()/100;
        }
    QString p=QString::number(prix_final);
    qry->prepare("INSERT INTO billet (id,nom,prenom,nombreper,evenement,prix)VALUES(id_auto_increment.nextval,'"+nom +"','"+prenom +"','"+nombreper +"','"+evenement +"','"+p +"');");

    if(qry->exec()){
        c.errormessage("ajout reussi");
         ui->nom->setText("");
        ui->prenom->setText("");
         ui->evenement->setText("");
        ui->nombreper->setText("");
    }
    else{
    c.successmessage("ajout non reussi");
    }
    }
    }
    else{
       c.errormessage("information manquante");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
      Connection c;
      bool validation = true;
      QString id,nom,prenom,evenement,nombreper,prix,query;
      id = ui->id->text();
      nom = ui->nom_2->text();
      prenom = ui->prenom_2->text();
      evenement = ui->evenement_2->text();
      nombreper = ui->nombreper_2->text();
      prix = ui->prix_2->text();
      if(!id.length()){
          c.errormessage("entre id du billet a modifier");
                  validation=false;
      }
      if(validation){
      QString types[5]={"nom","prenom","evenement","nombreper","prix"};
      QString inputs[5]={nom,prenom,evenement,nombreper,prix};
      query="update billet set";
      for(int i = 0; i < 5; i++) {
          QString et="";
          if(query != "update billet set"){
              et=",";
          }
        if(inputs[i].length()>0){
            query+=" "+et+" "+types[i]+" = '"+inputs[i]+"'";
        }
      }
    if(query == "update billet set"){
    c.errormessage("information manquante pour modifier");
    }
    else{
      query+=" where id='"+id+"'";

      c.createconnect();
      QSqlQuery* qry=new QSqlQuery(c.db);
      QSqlQuery* qry1=new QSqlQuery(c.db);
      qry1->prepare("select * from billet where id='"+id+"'");
      qry1->exec();
      QSqlQueryModel * modal= new QSqlQueryModel();
      modal->setQuery(*qry1);
      if(!modal->index(0,0).data().toString().length()){
         c.errormessage("id existe pas");
      }
      else{
      qry->prepare(query);
      qry->exec();
      if(qry->exec()){
          c.errormessage("modification reussi");
          ui->id->setText("");
          ui->nom_2->setText("");
          ui->prenom_2->setText("");
          ui->evenement_2->setText("");
          ui->nombreper_2->setText("");
          ui->nombreper_2->setText("");
      }
      else{
      c.successmessage("modification non reussi");
      }
      }


    }
     }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString id,nom,prenom,evenement,nombreper,prix,query;
       Connection c;
       id = ui->id->text();
       nom = ui->nom_2->text();
       prenom = ui->prenom_2->text();
       evenement = ui->evenement_2->text();
       nombreper = ui->nombreper_2->text();
       prix = ui->prix_2->text();
       QString types[6]={"id","nom","prenom","evenement","nombreper","prix"};
       QString inputs[6]={id,nom,prenom,evenement,nombreper,prix};
       query="Delete from billet where";
       for(int i = 0; i < 6; i++) {
         if(inputs[i].length()>0){
             query+=" "+types[i]+" = '"+inputs[i]+"'";
         }
       }
    if(query == "Delete from billet where" ){
     c.errormessage("information manquante pour supprimer");
    }
    else{

        c.createconnect();
        QSqlQuery* qry=new QSqlQuery(c.db);
        QSqlQuery* qry1=new QSqlQuery(c.db);
        qry1->prepare("select * from billet where id='"+id+"'");
        qry1->exec();
        QSqlQueryModel * modal= new QSqlQueryModel();
        modal->setQuery(*qry1);
        if(!modal->index(0,0).data().toString().length()){
           c.errormessage("id existe pas");
        }
        else{
        qry->prepare(query);
        qry->exec();
        if(qry->exec()){
            c.errormessage("supprimer reussi");
            ui->id->setText("");
            ui->nom_2->setText("");
            ui->prenom_2->setText("");
            ui->evenement_2->setText("");
            ui->nombreper_2->setText("");
            ui->nombreper_2->setText("");
        }
        else{
        c.successmessage("ajout non reussi");
        }
        }

    }
}



void MainWindow::on_pushButton_5_clicked()
{
     QString nom,prenom,evenement,nombreper,prix,query="select * from billet where";

     Connection c;
       nom = ui->nom_3->text();
       prenom = ui->prenom_3->text();
       evenement = ui->evenement_3->text();
       prix = ui->prix_3->text();
       QString types[4]={"nom","prenom","evenement","prix"};
       QString inputs[4]={nom,prenom,evenement,prix};
       for(int i = 0; i < 4; i++) {
           QString et="";
           if(query != "select * from billet where"){
               et="and";
           }
         if(inputs[i].length()>0){
             query+=" "+et+" "+types[i]+" = '"+inputs[i]+"'";
         }
       }
       if(query == "select * from billet where" ){
       c.errormessage("information manquante pour le filtre");
       }
        else{
        c.createconnect();
        QSqlQueryModel * modal= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery(c.db);
        qry->prepare(query);
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
       }
}

void MainWindow::on_calendarWidget_activated(const QDate &date)
{

    Connection c;
    QString dateTimeString = date.toString("dd/MM/yyyy");
    c.createconnect();
    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery(c.db);
    qry->prepare("select nom, temps from evenement where to_char(temps,'dd/MM/yyyy')= :date ;");
    qry->bindValue(":date",dateTimeString);
    qry->exec();
    modal->setQuery(*qry);
    QString info="";

    for(int row=0 ;row<100;row++){
        for(int col=0;col<2;col++){
              QVariant index =modal->index(row,col).data();
              if(!index.toString().length()){
                  if(!info.length()){
                     info="pas evenement";
                  }
                  c.errormessage(info);
                  return;
              }
            if(col ==1){
               info+=index.toTime().toString()+"\n ";
            }
            else{
            info+=index.toString()+"\n ";
            }
        }
        info+="\n";
    }





}

void MainWindow::on_pushButton_7_clicked()
{
    Connection c;
    bool validation = true;
    QString nom,prix;
    QDateTime date;
    nom = ui->nom_6->text();
    prix = ui->prix_5->text();
    date = ui->dateTimeEdit_2->dateTime();
    QString inputs[3]={nom,prix,date.toString("dd/MM/yyyy")};
     for(int i = 0; i < 3; i++) {
         if(inputs[i].length() == 0){
             validation = false;
         }
     }
    if(validation){
    c.createconnect();
    QSqlQuery* qry=new QSqlQuery(c.db);
        qry->prepare("INSERT INTO evenement (nom,prix,temps) VALUES ('"+nom +"','"+prix +"', :date) ;");

        QSqlQuery* qry1=new QSqlQuery(c.db);
        qry1->prepare("select * from evenement where nom='"+nom+"'");
        qry1->exec();
        QSqlQueryModel * modal= new QSqlQueryModel();
        modal->setQuery(*qry1);
        if(modal->index(0,0).data().toString().length()){
           c.errormessage("nom existe");
        }
        else{
         qry->bindValue(":date",date);
         if(qry->exec()){
        c.errormessage("ajout reussi");
        ui->nom_6->setText("");
        ui->prix_5->setText("");
         }
         else{
           c.errormessage("ajout non reussi");
         }
        }


    }
    else{
       c.errormessage("information manquante");
    }

}

void MainWindow::on_pushButton_8_clicked()
{

    Connection c;
    bool validation = true;
    QString nom,prix;
    QDateTime date;
    nom = ui->nom_6->text();
    prix = ui->prix_5->text();
    date = ui->dateTimeEdit_2->dateTime();
    if(!nom.length()){
        c.errormessage("entrer nom du evenement a modifier");
                validation=false;
    }
    if(validation){
    QString types[2]={"prix","temps"};
    QString inputs[2]={prix,date.toString("dd/MM/yyyy HH:mm")};
    QString query="update evenement set";
    for(int i = 0; i < 2; i++) {
        QString et="";
        if(query != "update evenement set"){
            et=",";
        }
      if(inputs[i].length()>0 && inputs[i] != "01/01/2000 00:00"){
         if(i==1){
         query+=" "+et+" "+types[i]+" = :date";
         }
         else{
          query+=" "+et+" "+types[i]+" = '"+inputs[i]+"'";
        }
      }

    }
  if(query == "update evenement set"){
  c.errormessage("information manquante pour modifier");
  }
  else{
    query+=" where nom='"+nom+"'";

    c.createconnect();
    QSqlQuery* qry=new QSqlQuery(c.db);
    QSqlQuery* qry1=new QSqlQuery(c.db);
    qry1->prepare("select * from evenement where nom='"+nom+"'");
    qry1->exec();
    QSqlQueryModel * modal= new QSqlQueryModel();
    modal->setQuery(*qry1);
    if(!modal->index(0,0).data().toString().length()){
       c.errormessage("nom existe pas");
    }
    else{
    qry->prepare(query);
    qry->bindValue(":date",date);
    if(qry->exec()){
        c.errormessage("modification reussi");
        ui->nom_6->setText("");
        ui->prix_5->setText("");
    }
    else{
        c.errormessage("modification non reussi");
    }
    }
  }
   }
}

void MainWindow::on_pushButton_9_clicked()
{
    QString nom,prix;
    QDateTime date;
       Connection c;
       nom = ui->nom_6->text();
       prix = ui->prix_5->text();
       date = ui->dateTimeEdit_2->dateTime();
       QString types[3]={"nom","prix","temps"};
       QString inputs[3]={nom,prix,date.toString("dd/MM/yyyy HH:mm")};
       QString query="Delete from evenement where";
       for(int i = 0; i < 3; i++) {
         if(inputs[i].length()>0 && inputs[i] != "01/01/2000 00:00"){
             if(i==2){
             query+=" "+types[i]+" = :date";
             }
             else{
             query+=" "+types[i]+" = '"+inputs[i]+"'";
            }
          }
       }
    if(query == "Delete from evenement where" ){
     c.errormessage("information manquante pour supprimer");
    }
    else{

       c.createconnect();
       QSqlQuery* qry=new QSqlQuery(c.db);
       QSqlQuery* qry1=new QSqlQuery(c.db);
       qry1->prepare("select * from evenement where nom='"+nom+"'");
       qry1->exec();
       QSqlQueryModel * modal= new QSqlQueryModel();
       modal->setQuery(*qry1);
       if(!modal->index(0,0).data().toString().length()){
          c.errormessage("nom existe pas");
       }
       else{
       qry->prepare(query);
       qry->bindValue(":date",date);
       if(qry->exec()){
           c.errormessage("supprimer reussi");
           ui->nom_6->setText("");
           ui->prix_5->setText("");
       }
       else{
           c.errormessage("supprimer non reussi");
       }
       }

    }
}

void MainWindow::on_pushButton_15_clicked()
{
    QString nom,prix;
    QDateTime date;
       Connection c;
       nom = ui->nom_4->text();
      date=ui->dateTimeEdit->dateTime();
       prix = ui->prix_4->text();
       QString types[3]={"nom","prix","temps"};
       QString inputs[3]={nom,prix,date.toString("dd/MM/yyyy HH:mm")};
       QString query="select * from evenement where";
       for(int i = 0; i < 3; i++) {
           QString et=" ";
           if(query != "select * from evenement where"){
               et="and ";
           }
         if(inputs[i].length()>0 && inputs[i] != "01/01/2000 00:00"){
             if(i==2){
             query+=" "+et+types[i]+" = :date";
             }
             else{
             query+=" "+et+types[i]+" = '"+inputs[i]+"'";
            }
          }
       }
    if(query == "select * from evenement where" ){
     c.errormessage("information manquante pour afficher");
    }
    else{

        QSqlQueryModel * modal= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery(c.db);
        qry->prepare(query);
        qry->bindValue(":date",date);
        qry->exec();
        modal->setQuery(*qry);
       ui->tableView_2->setModel(modal);

    }
}



void MainWindow::on_pushButton_10_clicked()
{
    Connection c;
    bool validation = true;
    QString nom;
    QString nombre_min,nombre_max,pourcentage;

    nom = ui->nom_5->text();
    pourcentage = ui->pourcentage->text();
    nombre_min= ui->nombreper_3->text();
    nombre_max=ui->nombreper_4->text();

if(!nom.length() || !pourcentage.length() ||nombre_min.toInt()>nombre_max.toInt()){
validation = false;
}


    if(validation){
    c.createconnect();
    QSqlQuery* qry=new QSqlQuery(c.db);
    qry->prepare("INSERT INTO offre (nomeve,minper,maxper,pourcentage) VALUES ('"+nom +"','"+nombre_min+"','"+nombre_max+"','"+pourcentage +"') ;");
    if(qry->exec()){
        ui->nom_5->setText("");
        ui->pourcentage->setText("");
        ui->nombreper_3->setText("");
        ui->nombreper_4->setText("");
        c.errormessage("ajout reussi");
    }
    else{
        c.errormessage("ajout non reussi");
    }

    }
    else{
       c.errormessage("information manquante ou fausse");
    }
}




void MainWindow::on_pushButton_11_clicked()
{
    Connection c;
    bool validation = true;
    QString nom;
    QString nombre_min,nombre_max,pourcentage;
    nom = ui->nom_5->text();
    pourcentage = ui->pourcentage->text();
    nombre_min= ui->nombreper_3->text();
    nombre_max=ui->nombreper_4->text();
    if(!nom.length()){
        c.errormessage("entrer nom du evenement du offre a modifier");
                validation=false;
    }
    if(validation){
    QString types[3]={"minper","maxper","pourcentage"};
    QString inputs[3]={nombre_min,nombre_max,pourcentage};
    QString query="update offre set";
    for(int i = 0; i < 3; i++) {
        QString et="";
        if(query != "update offre set"){
            et=",";
        }

            if(inputs[i].length()){
         query+=" "+et+" "+types[i]+" = '"+inputs[i]+"'";
       }


    }
  if(query == "update offre set"){
  c.errormessage("information manquante pour modifier");
  }
  else{
    query+=" where nomeve='"+nom+"'";

    c.createconnect();
    QSqlQuery* qry=new QSqlQuery(c.db);
    qry->prepare(query);
    if(qry->exec()){
            ui->nom_5->setText("");
            ui->pourcentage->setText("");
            ui->nombreper_3->setText("");
            ui->nombreper_4->setText("");
            c.errormessage("modification reussite");
        }
        else{
            c.errormessage("modification non reussite");
        }

  }
   }
}

void MainWindow::on_pushButton_12_clicked()
{
    Connection c;
    QString nom;
    QString nombre_min,nombre_max,pourcentage;
    nom = ui->nom_5->text();
    pourcentage = ui->pourcentage->text();
    nombre_min= ui->nombreper_3->text();
    nombre_max=ui->nombreper_4->text();

    QString types[4]={"nomeve","minper","maxper","pourcentage"};
    QString inputs[4]={nom,nombre_min,nombre_max,pourcentage};
    QString query="delete from offre where";
    for(int i = 0; i < 4; i++) {
        QString et="";
        if(query != "delete from offre where"){
            et=",";
        }

            if(inputs[i].length()){
         query+=" "+et+" "+types[i]+" = '"+inputs[i]+"'";
       }


    }
  if(query == "delete from offre where"){
  c.errormessage("information manquante pour supprimer");
  }
  else{


    c.createconnect();
    QSqlQuery* qry=new QSqlQuery(c.db);
    qry->prepare(query);
    if(qry->exec()){
            ui->nom_5->setText("");
            ui->pourcentage->setText("");
            ui->nombreper_3->setText("");
            ui->nombreper_4->setText("");
            c.errormessage("supprimer reussite");
        }
        else{
            c.errormessage("supprimer non reussite");
        }


  }

}

void MainWindow::on_pushButton_16_clicked()
{
    Connection c;
    QString nom;
    QString nombre_min,nombre_max,pourcentage;
    nom = ui->nom_13->text();
    pourcentage = ui->pourcentage_3->text();
    nombre_min= ui->nombreper_9->text();
    nombre_max=ui->nombreper_10->text();

    QString types[4]={"nomeve","minper","maxper","pourcentage"};
    QString inputs[4]={nom,nombre_min,nombre_max,pourcentage};
    QString query="select * from offre where";
    for(int i = 0; i < 4; i++) {
        QString et="";
        if(query != "select * from offre where"){
            et="and";
        }

            if(inputs[i].length()){
         query+=" "+et+" "+types[i]+" = '"+inputs[i]+"'";
       }


    }
  if(query == "select * from offre where"){
  c.errormessage("information manquante pour afficher");
  }
  else{


      Connection c;
      c.createconnect();
      QSqlQueryModel * modal= new QSqlQueryModel();
      QSqlQuery* qry=new QSqlQuery(c.db);
      qry->prepare(query);
      qry->exec();
      modal->setQuery(*qry);
      ui->tableView_3->setModel(modal);



  }

}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    Connection c;
    c.createconnect();
    if (index>=0){
        double total;
        QMap <QString , double> mp;
        QSqlQuery qry;
        qry.prepare("select nom from evenement");
        qry.exec();
         QSqlQueryModel * modal= new QSqlQueryModel();
         modal->setQuery(qry);

            QBarSeries *series = new QBarSeries();
            for(int i=0;i<6;i++){
                QSqlQuery qry1;
                QString nomeve=modal->index(i,0).data().toString();
                if(nomeve.length()){
               QBarSet *set0 = new QBarSet(nomeve);
              qry1.prepare("select sum(prix) from billet where evenement='"+ nomeve +"' ");
              qry1.exec();
              QSqlQueryModel * modal1= new QSqlQueryModel();
              modal1->setQuery(qry1);
              double value=modal1->index(0,0).data().toDouble();
              total +=value;
                 mp.insert(nomeve,value);
                 *set0 << value ;
                   series->append(set0);
                   series->setLabelsVisible(set0);
                   qry1.finish();
        }

            }


            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("les valeurs des profits des événements en dinars");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            QStringList categories;
            categories << "" ;
            QBarCategoryAxis *axis = new QBarCategoryAxis();
            axis->append(categories);
            chart->createDefaultAxes();
            chart->setAxisX(axis, series);

            QPieSeries *series1=new QPieSeries;
            for(QMap<QString,double> ::iterator itr=mp.begin();itr!=mp.end();itr++ ){
                double pourcentage= itr.value()/total;
                 QString pour;
                if(floor(pourcentage*100)+0.5<=pourcentage*100){
                 pour =QString::number(ceil(pourcentage*100));
                }
                else{
                    pour =QString::number(floor(pourcentage*100));
                }
            series1->append(itr.key()+"  "+pour+"%",pourcentage);

            }
            series1->setLabelsVisible();
            QChart *chart1 = new QChart();
            chart1->addSeries(series1);
            chart1->setTitle("les pourcentages des profits des événements");
            QChartView *chartView = new QChartView(chart);
            QChartView *chartView1 = new QChartView(chart1);
            chartView->setParent(ui->horizontalFrame);
            chartView1->setParent(ui->horizontalFrame_3);
    }
    if(index==2){
    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQueryModel * modal1= new QSqlQueryModel();
    QSqlQueryModel * modal2= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery(c.db);
    qry->prepare("select * from billet;");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView_2->setModel(modal1);
    ui->tableView_3->setModel(modal2);
}
    else if(index==3){
        QSqlQueryModel * modal= new QSqlQueryModel();
        QSqlQueryModel * modal1= new QSqlQueryModel();
        QSqlQueryModel * modal2= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery(c.db);
        qry->prepare("select * from evenement;");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal1);
        ui->tableView_2->setModel(modal);
        ui->tableView_3->setModel(modal2);
    }
    else if(index==6){
        QSqlQueryModel * modal= new QSqlQueryModel();
        QSqlQueryModel * modal1= new QSqlQueryModel();
        QSqlQueryModel * modal2= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery(c.db);
        qry->prepare("select * from offre;");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal2);
        ui->tableView_2->setModel(modal1);
        ui->tableView_3->setModel(modal);

    }


}

void MainWindow::on_pushButton_2_clicked()
{
    int id=ui->id_per->text().toInt();
     QString nom=ui->nom_per->text();
      QString prenom=ui->prenom_per->text();
       QString email=ui->email_per->text();
Personne p(id,email,nom,prenom);
bool test=p.ajouter();
QMessageBox msg;
if(test){
    msg.setText("ajout reussi");
}
else{
    msg.setText("ajout non reussi");
}
msg.exec();
}

void MainWindow::on_tabWidget_3_currentChanged(int index)
{
   if (index ==2){
       Personne p;
       ui->tableView_4->setModel(p.afficher());
   }
}

void MainWindow::on_pushButton_6_clicked()
{
    int id=ui->id_mod_per->text().toInt();
     QString nom=ui->nom_mod_per->text();
      QString prenom=ui->prenom_mod_per->text();
       QString email=ui->email_mod_per->text();
       QMessageBox msg;
Personne p(id,email,nom,prenom);
QSqlQueryModel* modal = p.afficherRecherche(id);
if(!modal->index(0,0).data().toString().length()){
    msg.setText("id existe pas ");
}
else{
bool test=p.modifier(id);

if(test){
    msg.setText("modification reussi");
}
else{
    msg.setText("modification non reussi");
}
}
msg.exec();
}

void MainWindow::on_pushButton_13_clicked()
{
    int id=ui->id_supp_per->text().toInt();

       QMessageBox msg;
Personne p;
QSqlQueryModel* modal = p.afficherRecherche(id);
if(!modal->index(0,0).data().toString().length()){
    msg.setText("id existe pas ");
}
else{
bool test=p.supprimer(id);

if(test){
    msg.setText("supprimer reussi");
}
else{
    msg.setText("supprimer non reussi");
}
}
msg.exec();
}

void MainWindow::on_pushButton_29_clicked()
{
 Personne p;

    ui->tableView_4->setModel(p.afficher());
}

void MainWindow::on_pushButton_28_clicked()
{
    Personne p;
   int id=ui->id_rech_per->text().toInt();
       ui->tableView_4->setModel(p.afficherRecherche(id));
}

void MainWindow::on_pushButton_30_clicked()
{
    Personne p;

       ui->tableView_4->setModel(p.afficherTri(0));
}

void MainWindow::on_pushButton_14_clicked()
{
    int mat=ui->mat_par->text().toInt();
     QString nom=ui->nom_par->text();
      QString prenom=ui->prenom_par->text();
       int prix=ui->prix_par->text().toInt();
       int periode=ui->periode_par->text().toInt();
Parking p(mat,nom,prenom,periode,prix);
bool test=p.ajouter();
QMessageBox msg;
if(test){
    msg.setText("ajout reussi");
}
else{
    msg.setText("ajout non reussi");
}
msg.exec();
}

void MainWindow::on_pushButton_17_clicked()
{
    int mat=ui->mat_par_mod->text().toInt();
     QString nom=ui->nom_par_mod->text();
      QString prenom=ui->prenom_par_mod->text();
       int prix=ui->prix_par_mod->text().toInt();
       int periode=ui->periode_par_mod->text().toInt();
Parking p(mat,nom,prenom,periode,prix);
QMessageBox msg;
QSqlQueryModel* modal = p.rechercher_matricule(mat);
if(!modal->index(0,0).data().toString().length()){
    msg.setText("matricule existe pas ");
}
else{
bool test=p.modifier();

if(test){
    msg.setText("modification reussi");
}
else{
    msg.setText("modification non reussi");
}
}
msg.exec();
}

void MainWindow::on_pushButton_18_clicked()
{
    int mat=ui->mat_par_supp->text().toInt();

       QMessageBox msg;
Parking p;
QSqlQueryModel* modal = p.rechercher_matricule(mat);
if(!modal->index(0,0).data().toString().length()){
    msg.setText("matricule existe pas ");
}
else{
bool test=p.supprimer(mat);

if(test){
    msg.setText("supprimer reussi");
}
else{
    msg.setText("supprimer non reussi");
}
}
msg.exec();
}

void MainWindow::on_pushButton_31_clicked()
{
    Parking p;
   int mat=ui->mat_par_rech->text().toInt();
       ui->tableView_5->setModel(p.rechercher_matricule(mat));
}

void MainWindow::on_pushButton_40_clicked()
{
    Parking p;
       ui->tableView_5->setModel(p.afficher());
}

void MainWindow::on_pushButton_32_clicked()
{
    Parking p;
       ui->tableView_5->setModel(p.trier());
}

void MainWindow::on_tabWidget_4_currentChanged(int index)
{
    if(index == 2){
        Parking p;
        ui->tableView_5->setModel(p.afficher());
    }
}

void MainWindow::on_pushButton_22_clicked()
{QString nom=ui->nom_ser->text();
    QString produit=ui->produit_ser->text();
    QString etat_financiere=ui->etat_ser->text();
    QString raison_social=ui->social_ser->text();
    QString etablissement=ui->eta_ser->text();
    QString description=ui->textEdit->toPlainText();
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



void MainWindow::on_pushButton_24_clicked()
{
    QString nom=ui->nom_ser_supp->text();
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


void MainWindow::on_pushButton_42_clicked()
{
    QSqlQueryModel* req=new QSqlQueryModel();;
    req->setQuery("select nom,produit,etat_financiere,raison_social,etablissement,description from servi");


    ui->tableView_7->setModel(req);
}



void MainWindow::on_pushButton_23_clicked()
{QString nom=ui->nom_ser_mod->text();
    QString produit=ui->produit_ser_mod->text();
    QString etat_financiere=ui->etat_ser_mod->text();
    QString raison_social=ui->raison_ser_mod->text();
    QString etablissement=ui->etabl_ser_mod->text();
    QString description=ui->textEdit_2->toPlainText();
    QSqlQuery qry;
    qry.prepare("update servi set  etat_financiere='"+etat_financiere+"',raison_social='"+raison_social+"',description='"+description+"',produit='"+produit+"',etablissement='"+etablissement+"'where nom='"+nom+"'  " );
    if(qry.exec())
    {

        QMessageBox::critical(this,"edit","updated");
    }
    else
    {
        QMessageBox::critical(this,"error"," not updated");

    }

}

void MainWindow::on_pushButton_35_clicked()
{
    QString nom=ui->nom_ser_rech->text();
    QSqlQuery qry;
    qry.prepare("select * from servi where nom='"+nom+"'");
    if(qry.exec())
    {QSqlQueryModel * model=new QSqlQueryModel();


        model->setQuery(qry);
        ui->tableView_7->setModel(model);

    }
    else
    {
        QMessageBox::warning(this,"error","no information");
    }
}

void MainWindow::on_pushButton_38_clicked()
{
    QSqlQuery qry;
    qry.prepare("select * from servi ORDER BY nom");
    if(qry.exec())


    {
        QSqlQueryModel * model=new QSqlQueryModel();


                model->setQuery(qry);
                ui->tableView_7->setModel(model);

    }
    else {
        QMessageBox::warning(this,"error","no information");
    }
}

void MainWindow::on_tabWidget_6_currentChanged(int index)
{
    if(index == 2 ){
        on_pushButton_42_clicked();
    }
}

void MainWindow::on_pushButton_19_clicked()
{
    int cin=ui->cin_per->text().toInt();
           QString nom=ui->nom_per_2->text();
           QString prenom=ui->prenom_per_2->text();
           QString adresse=ui->adresse_per_2->text();
           QDate date_n=ui->dateEdit->date();

           personnel p(cin,nom,prenom,adresse,date_n);

           bool test=p.ajouter();
           if(test)
           {
               ui->tableView_3->setModel(p.afficher());
                 QMessageBox::information(nullptr, QObject::tr("OK") ,
                                          QObject::tr("Ajout effectué "
                                                      "Clicked Cancel to exit.") , QMessageBox::Cancel);
           }
           else
                 QMessageBox::critical(nullptr, QObject::tr("not OK") ,
                                          QObject::tr("Ajout non effectué "
                                                      "Clicked Cancel to exit.") , QMessageBox::Cancel);
}

void MainWindow::on_pushButton_20_clicked()
{

        int cin=ui->cin_per_7->text().toInt();
           QString nom=ui->nom_per_7->text();
           QString prenom=ui->prenom_per_7->text();
           QString adresse=ui->adresse_per_10->text();
           QDate date_n=ui->dateEdit_3->date();
 personnel p(cin,nom,prenom,adresse,date_n);
       bool test= p.modifier(cin);
        QMessageBox msg;
       if(test)
       {
                       msg.setText("modifie avec succés");

                       }
                       else
                       {
                       msg.setText("Echec au niveau de la modif ");
                       }
                       msg.exec();


}

void MainWindow::on_pushButton_21_clicked()
{
    int cin=ui->cin_supp_per_3->text().toInt();
    personnel p;
          bool test=p.supprimer(cin);
          if(test)
          {


                QMessageBox::information(nullptr, QObject::tr("OK") ,
                                         QObject::tr("Supression effectué "
                                                     "Clicked Cancel to exit.") , QMessageBox::Cancel);
          }
          else
                QMessageBox::critical(nullptr, QObject::tr("not OK") ,
                                         QObject::tr("Suppression non effectué "
                                                     "Clicked Cancel to exit.") , QMessageBox::Cancel);
}

void MainWindow::on_pushButton_33_clicked()
{
    personnel p;
    QString nom = ui->nom_rech_per_8->text();
    ui->tableView_6->setModel(p.rechercheNom(nom));
}

void MainWindow::on_pushButton_41_clicked()
{
    personnel p;

    ui->tableView_6->setModel(p.afficher());
}

void MainWindow::on_pushButton_37_clicked()
{
    personnel p;

    ui->tableView_6->setModel(p.triernom());
}

void MainWindow::on_pushButton_25_clicked()
{
            int Id=ui->id_per_5->text().toInt();
               QString nom=ui->nom_per_5->text() ;
               QString prenom=ui->prenom_per_5->text() ;
               int nombre_des_jeux=ui->nb_per_5->text().toInt();
               int duree=ui->duree_per_15->text().toInt();
               int prix=ui->prix_per_9->text().toInt();
               int etat=ui->etat_per_16->text().toInt();
               QDate date =ui->dateEdit_2->date();
               QString strDate = date.toString("dd-MM-yyyy");

               //affectation des donnees
               Abonnement A(Id,nom,prenom,nombre_des_jeux,prix,duree,etat,strDate);

                       bool test=A.ajouter();
                   if(test)
                               {

                                  QMessageBox msgBox ;
                                  QMessageBox::information(this,"information","abbonement ajouté");
                                  }
                                   else
                                   {
                                       QMessageBox msgBox ;
                                       msgBox.setText("abbonement non ajouté ");
                                   }


}

void MainWindow::on_pushButton_26_clicked()
{
    int Id=ui->id_per_9->text().toInt();
       QString nom=ui->nom_per_9->text() ;
       QString prenom=ui->prenom_per_10->text() ;
       int nombre_des_jeux=ui->nb_per_18->text().toInt();
       int duree=ui->duree_per_19->text().toInt();
       int prix=ui->prix_per_11->text().toInt();
       int etat=ui->etat_per_20->text().toInt();
       QDate date =ui->dateEdit_4->date();
       QString strDate = date.toString("dd-MM-yyyy");

       //affectation des donnees
       Abonnement A(Id,nom,prenom,nombre_des_jeux,prix,duree,etat,strDate);

               bool test=A.modifier(Id);
           if(test)
                       {

                          QMessageBox msgBox ;
                          QMessageBox::information(this,"information","abbonement modifié");
                          }
                           else
                           {
                               QMessageBox msgBox ;
                               msgBox.setText("abbonement non modifié ");
                           }
}

void MainWindow::on_pushButton_27_clicked()
{
   int Id=ui->id_supp_per_5->text().toInt();

   Abonnement A;

           bool test=A.supprimer(Id);
       if(test)
                   {

                      QMessageBox msgBox ;
                      QMessageBox::information(this,"information","abbonement supprime");
                      }
                       else
                       {
                           QMessageBox msgBox ;
                           msgBox.setText("abbonement non supprimé ");
                       }
}

void MainWindow::on_pushButton_36_clicked()
{
      QString Id=ui->id_supp_per_11->text();
       Abonnement A;
       ui->tableView_8->setModel(A.rechercher(Id));

}

void MainWindow::on_pushButton_43_clicked()
{
    Abonnement A;
    ui->tableView_8->setModel(A.afficher());
}

void MainWindow::on_pushButton_39_clicked()
{
    Abonnement A;
    ui->tableView_8->setModel(A.trier());
}

void MainWindow::on_tabWidget_7_currentChanged(int index)
{
    if (index ==2){
       on_pushButton_43_clicked();
    }
}

void MainWindow::on_tabWidget_5_currentChanged(int index)
{
    if (index ==2){
       on_pushButton_41_clicked();
    }
}

void MainWindow::on_tabWidget_2_currentChanged(int index)
{
  QMessageBox msg;
    if(!validationClient && !validationAdmin){
      ui->tabWidget_2->setCurrentIndex(0);
        msg.setText("authentifiez-vous");
        msg.exec();
  }
  else if(validationClient){
      if(!index || index==4){
         ui->tabWidget_2->setCurrentIndex(1);
      }
      if(index==4){
        msg.setText("vous etes pas admin");
         msg.exec();
      }
  }
  else{
      if(!index){
         ui->tabWidget_2->setCurrentIndex(1);
    }
  }
}

void MainWindow::on_pushButton_34_clicked()
{
    QString cle1=ui->cle1->text();
    QMessageBox msg;
    if(cle1 == "smart parking perso2022"){
        validationClient = true;
        ui->tabWidget_2->setCurrentIndex(1);
        msg.setText("authentification client reussi");
    }
    else{
        msg.setText("authentification client non reussi");
    }
    msg.exec();
}

void MainWindow::on_pushButton_44_clicked()
{
    QString cle1=ui->cle->text();
    QMessageBox msg;
    if(cle1 == "smart parking admin 000 in 2022"){
        validationAdmin = true;
        ui->tabWidget_2->setCurrentIndex(1);
        msg.setText("authentification admin reussi");
    }
    else{
        msg.setText("authentification admin non reussi");
    }
    msg.exec();
}

void MainWindow::on_pushButton_45_clicked()
{
    QMessageBox msg;
    if(validationAdmin || validationClient){
        validationAdmin =false;
        validationClient = false;
         msg.setText("utilistateur deconnecte");
         ui->tabWidget_2->setCurrentIndex(0);
    }
    else{
         msg.setText("utilistateur est pas connecte");
    }
    msg.exec();
}
