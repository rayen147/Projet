#ifndef DIALOGADMIN_H
#define DIALOGADMIN_H

#include <QDialog>

namespace Ui {
class DialogAdmin;
}

class DialogAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdmin(QWidget *parent = nullptr);
    ~DialogAdmin();

private:
    Ui::DialogAdmin *ui;
};

#endif // DIALOGADMIN_H
