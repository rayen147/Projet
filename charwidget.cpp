#include "charwidget.h"


charwidget::charwidget()
{

}
void charwidget::painteven(QPaintEvent *)
{
 QPainter painter(this);
 QRectF size = QRectF(10,10,this->width()-10,this->width()-10);
 painter.setBrush(Qt::red);
 painter.drawPie(size,0,90*16);
 painter.setBrush(Qt::blue);
 painter.drawPie(size,90*16,270*16);

}