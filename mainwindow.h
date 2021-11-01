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

private:
    Ui::MainWindow *ui;
    Parking P;
};

#endif // MAINWINDOW_H
