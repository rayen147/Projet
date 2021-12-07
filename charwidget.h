#ifndef CHARWIDGET_H
#define CHARWIDGET_H

#include <QWidget>
#include <QPainter>
class charwidget: public QWidget
{
public:
    charwidget();
protected:
     void painteven(QPaintEvent *);
};

#endif // CHARWIDGET_H
