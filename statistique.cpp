#include "statistique.h"
#include <QPainter>
statistique::statistique(QWidget *parent) : QWidget(parent)
{

}

void statistique::setData(QVector<double> value, QVector<QColor> colors)
{qvValues=value;
    qvColors=colors;
    repaint();
    update();

}

void statistique::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
   QPen pen;
   QRectF size;
   pen.setColor(Qt::black);
   pen.setWidth(2);
  painter.setPen(pen);
  if(this->width()>this->height())
  {
      size=QRectF(5,5,this->width()-10,this->width()-10);

  }
  else {
      size=QRectF(5,5,this->height()-10,this->height()-10);
  }
  double sum=0.0,startangle=0.0;
  double angle,endangle,percent;
  for(int i=0;i<qvValues.size();i++)
  {
      sum+=qvValues[i];
  }
  for(int i=0;i<qvValues.size();i++)
  {
      percent = qvValues[i]/sum;
      angle=percent*360.0;
      endangle=startangle+angle;
      painter.setBrush(qvColors[i]);
      painter.drawPie(size,startangle*16,angle*16);
      startangle=endangle;
  }

}

