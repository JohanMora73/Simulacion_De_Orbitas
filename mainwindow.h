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
#include <fstream>
#include <stdlib.h>
#include <string>
#include "planeta.h"
#include "sol.h"

using namespace std;

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
    void MostrarPlanetas(int num);
    void Escribir();
    void Escribir1();

public slots:
    //void Simulacion();
    void simulacion();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *time;
    float xi,yi,ancho,alto; //para darle el tamaño a la pantalla
    Planeta *sol, *Venus, *Tierra, *Marte, *Jupiter, *Urano;
    //Sol *sol;
    QList<Planeta *>planetas;
    QList<Planeta *>::iterator it;
    //QList<Planeta *>::iterator it2;
    double T=0.05,ax,ay,r,r1,r2,r3,r4,G=1,h=300;//G=6.674*pow(10,-11);
    double x,y,vx,vy;

    double *px;// = new double[6];
    double *py;// = new double[6];
    double *Vx;// = new double[6];
    double *Vy;// = new double[6];

    double xs,ys,vxs,vys;//sol
    double xv,yv,vxv,vyv;//Venus
    double xt,yt,vxt,vyt;//Tierra
    double xm,ym,vxm,vym;//Marte
    double xj,yj,vxj,vyj;//Jupiter
    double xu,yu,vxu,vyu;//Urano
    int contador;

    bool band=true;;

    int num;

};
#endif // MAINWINDOW_H
