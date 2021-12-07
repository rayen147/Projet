#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QWidget>

class statistique : public QWidget
{
    Q_OBJECT
public:
    explicit statistique(QWidget *parent = nullptr);
    void setData(QVector<double> value,QVector<QColor>colors);
protected :

    void paintEvent(QPaintEvent *);

private :
    QVector<double>qvValues;
    QVector<QColor>qvColors;



signals:

};

#endif // STATISTIQUE_H
