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
    
    void on_lineEdit_inputRejected();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *time;
    float xi,yi,ancho,alto; //para darle el tamaño a la pantalla
    Planeta *Mercurio, *Venus, *Tierra, *Marte, *Jupiter;
    Sol *sol;   
    double xk,yk,vxk,vyk,T=0.05,m=70,ax,ay,r,xs,ys,G=1;//G=6.674*pow(10,-11);
    bool band=true;;

};
#endif // MAINWINDOW_H
