#include "sol.h"

Sol::Sol()
{

}

Sol::Sol(int masa_, int radio_)
{
    posx=0;
    posy=0;
    masa=masa_;
    radio=radio_/10;
    ancho=2*radio;
    alto=2*radio;
    setPos(425,300);
}

int Sol::getPosx() const
{
    return posx;
}

void Sol::setPosx(int px)
{
    posx=px;
}

int Sol::getPosy() const
{
    return posy;
}

void Sol::setPosy(int py)
{
    posy=py;
}

QRectF Sol::boundingRect() const
{
    return QRectF(-radio,-radio,ancho,alto);
}

void Sol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
}
