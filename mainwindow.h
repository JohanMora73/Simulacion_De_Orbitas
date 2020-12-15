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
    int velocidad(int mi);

public slots:
    void simulacion();

private slots:
    void on_pushButton_clicked();
    
    void on_lineEdit_inputRejected();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *time;
    float xi,yi,ancho,alto; //para darle el tamaño a la pantalla
    Planeta *Venus, *Tierra, *Marte, *Jupiter, *Urano;
    Sol *sol;   
    double T=0.05,ax,ay,r,r1,r2,r3,r4,G=1,h=300;//G=6.674*pow(10,-11);

    double xs,ys;
    double xv,yv,vxv,vyv;//Venus
    double xt,yt,vxt,vyt;//Tierra
    double xm,ym,vxm,vym;//Marte
    double xj,yj,vxj,vyj;//Jupiter
    double xu,yu,vxu,vyu;//Urano

    bool band=true;;

};
#endif // MAINWINDOW_H
