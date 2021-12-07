#include "interfaceadmin.h"
#include "ui_interfaceadmin.h"

Interfaceadmin::Interfaceadmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Interfaceadmin)
{
    ui->setupUi(this);
}

Interfaceadmin::~Interfaceadmin()
{
    delete ui;
}
