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
    Planeta(int x, int y, int masa_, int radio, double vx, double vy, Qt::GlobalColor _color);
    QPixmap *pixmap;

    Qt::GlobalColor color;
    int posx,posy,masa,radio;
    float ancho,alto;
    double vx,vy;


    void posicion();//asigna la posicon de los planetas

    int getPosx() const;
    void setPosx(int px);
    int getPosy() const;
    void setPosy(int py);


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

#endif // PLANETA_H
