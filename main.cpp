#include "dialogmain.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialogmain w;
    Connexion c;
    bool test=c.ouvrirConnexion();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Ok);
}
else

        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    return a.exec();
}
