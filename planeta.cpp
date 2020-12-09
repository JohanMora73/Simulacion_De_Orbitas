#include "planeta.h"

Planeta::Planeta()
{
    
}

Planeta::Planeta(int x, int y, int masa_, int radio_, float vx_, float vy_)
{
    posx=425+x/30;
    posy=y/30;
    masa=masa_;
    radio=radio_/10;
    vx=vx_;
    vy=vy_;
    ancho=2*radio;
    alto=2*radio;


}

int Planeta::getPosx() const
{
    return posx;
}

void Planeta::setPosx(int px)
{
    posx=px;
}

int Planeta::getPosy() const
{
    return posy;
}

void Planeta::setPosy(int py)
{
    posy=py;
}

QRectF Planeta::boundingRect() const
{
    return QRectF(-radio,-radio,ancho,alto);
}

void Planeta::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect());
}
