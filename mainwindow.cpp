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
    Tierra=new Planeta(5000,0,70,70,0,100);
    scene->addItem(Tierra);
    sol=new Sol(70000,300);
    scene->addItem(sol);
    //scene->setBackgroundBrush(QPixmap(":/imagenes/cosmos-1866820_960_720.jpg"));
    ui->graphicsView->setScene(scene);
    connect(time,SIGNAL(timeout()),this,SLOT(simulacion()));

    x=Tierra->getPosx();
    y=Tierra->getPosy();
    vx=Tierra->vx;
    vy=Tierra->vy;

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
    if(band) time->start(int(T*1000));
    else time->stop();
    band=!band;
}
void MainWindow::simulacion()
{
    G=6.674*pow(10,-11);
    r=sqrt(pow(x*30,2)+pow(y*30,2));
    ax=(G*sol->masa*(-x*30))/pow(r,3);
    ay=(G*sol->masa*(-y*30))/pow(r,3);
    vy+=ax*T;
    vy+=ay*T;
    x+=vx*T;
    y+=vy*T;
    Tierra->setPosx(x);
    Tierra->setPosy(nuevoy(int(y)));
    Tierra->setPos(x,nuevoy(int(y)));
}
