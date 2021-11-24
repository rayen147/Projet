#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"parking.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_Ajouter_clicked();

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_recherche_matricule_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_recherche_nom_clicked();

    void on_recherche_prenom_clicked();

    void on_Ajouter_currentChanged(int index);

    void on_pb_qr_clicked();

private:
    Ui::MainWindow *ui;
    Parking P;
};

#endif // MAINWINDOW_H
