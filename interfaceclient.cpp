#include "interfaceclient.h"
#include "ui_interfaceclient.h"

Interfaceclient::Interfaceclient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Interfaceclient)
{
    ui->setupUi(this);
}

Interfaceclient::~Interfaceclient()
{
    delete ui;
}
