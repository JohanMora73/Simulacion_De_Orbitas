#ifndef PLANETA_H
#define PLANETA_H

#include <QPixmap>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Planeta: public QGraphicsItem, public QObject
{
public:
    Planeta();
    Planeta(int x, int y, int masa_, int radio, float vx, float vy);
    QPixmap *pixmap;

    int posx,posy,masa,radio;
    float ancho,alto,vx,vy;
    int getPosx() const;
    void setPosx(int px);
    int getPosy() const;
    void setPosy(int py);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

#endif // PLANETA_H
