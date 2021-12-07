#ifndef INTERFACEADMIN_H
#define INTERFACEADMIN_H

#include <QDialog>

namespace Ui {
class Interfaceadmin;
}

class Interfaceadmin : public QDialog
{
    Q_OBJECT

public:
    explicit Interfaceadmin(QWidget *parent = nullptr);
    ~Interfaceadmin();

private:
    Ui::Interfaceadmin *ui;
};

#endif // INTERFACEADMIN_H
