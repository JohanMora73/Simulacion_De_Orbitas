#ifndef SOL_H
#define SOL_H

#include <QPixmap>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Sol:public QGraphicsItem, public QObject
{
public:
    Sol();
    Sol(int masa_, int radio_);
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

#endif // SOL_H
