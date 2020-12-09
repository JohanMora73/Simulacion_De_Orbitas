#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QtDebug>
#include <QRect>
#include <QDesktopWidget>
#include <math.h>
#include "planeta.h"
#include "sol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int nuevoy(int y);

public slots:
    void simulacion();

private slots:
    void on_pushButton_clicked();
    
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *time;
    float xi,yi,ancho,alto; //para darle el tamaño a la pantalla
    Planeta *Tierra;
    Sol *sol;
    float x,y,vx,vy,T=0.05,m=70,ax,ay,G=6.674*pow(10,11),r;
    bool band=true;;

};
#endif // MAINWINDOW_H
