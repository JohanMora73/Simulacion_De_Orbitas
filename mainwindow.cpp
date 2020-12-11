#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xi=0;
    yi=0;
    ancho=850;
    alto=600;
    scene=new QGraphicsScene(xi,yi,ancho,alto);
    time= new QTimer;

    Mercurio =new Planeta();
    Venus=new Planeta();
    Tierra=new Planeta(5000,0,70,70,0,2);
    Marte=new Planeta();
    Jupiter=new Planeta();

    scene->addItem(Tierra);
    sol=new Sol(70000,300);
    scene->addItem(sol);
    scene->setBackgroundBrush(QPixmap(":/imagenes/fondodeff.jpg"));
    ui->graphicsView->setScene(scene);
    connect(time,SIGNAL(timeout()),this,SLOT(simulacion()));

    xk=Tierra->getPosx();
    yk=Tierra->getPosy();
    vxk=Tierra->vx;
    vyk=Tierra->vy;

    xs=sol->getPosx();
    ys=sol->getPosy();


    //y=nuevoy(Tierra->getPosy());
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::nuevoy(int y)
{
    return 300-y;;
}

void MainWindow::on_pushButton_clicked()
{
    if(band) time->start(int(T*10));
    else time->stop();
    band=!band;
}
void MainWindow::simulacion()
{

    r=sqrt(pow((xs-xk),2)+pow((ys-yk),2));
    ax=(G*sol->masa*(xs-xk))/pow(r,3);
    ay=(G*sol->masa*(ys-yk))/pow(r,3);
    vxk+=ax*T;
    vyk+=ay*T;
    xk+=vxk*T;
    yk+=vyk*T;
    Tierra->setPosx((xk/20)+425);
    Tierra->setPosy(nuevoy(int(yk/20)));
    Tierra->setPos((xk/20)+425,nuevoy(int(yk/20)));
}

void MainWindow::on_lineEdit_inputRejected()
{

}
