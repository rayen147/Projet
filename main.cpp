#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QFile>
#include<QLatin1String>
#include <QIODevice>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        QFile styleSheetFile("C:/Users/dell/Downloads/Adaptic/Adaptic.qss");
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        a.setStyleSheet(styleSheet);
        styleSheetFile.close();
         MainWindow w;

        w.show();








    return a.exec();
}
