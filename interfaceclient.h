#ifndef INTERFACECLIENT_H
#define INTERFACECLIENT_H

#include <QDialog>

namespace Ui {
class Interfaceclient;
}

class Interfaceclient : public QDialog
{
    Q_OBJECT

public:
    explicit Interfaceclient(QWidget *parent = nullptr);
    ~Interfaceclient();

private:
    Ui::Interfaceclient *ui;
};

#endif // INTERFACECLIENT_H
