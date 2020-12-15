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

    Urano=new Planeta(4000,5000,25,100,-1.6,1.2,Qt::cyan);
    Venus=new Planeta(1,1,0,1,0,0,Qt::magenta);
    Tierra=new Planeta(0,-7000,70,120,2,0,Qt::green);
    Marte=new Planeta(0,-5000,0,70,0,0,Qt::red);
    Jupiter=new Planeta(0,5000,0,70,0,0,Qt::gray);

    scene->addItem(Tierra);
    scene->addItem(Urano);
    scene->addItem(Marte);
    scene->addItem(Jupiter);

    sol=new Sol(70000,300);
    scene->addItem(sol);
    scene->setBackgroundBrush(QPixmap(":/imagenes/fondodeff.jpg"));
    ui->graphicsView->setScene(scene);
    connect(time,SIGNAL(timeout()),this,SLOT(simulacion()));

    xt=Tierra->getPosx();
    yt=Tierra->getPosy();
    vxt=Tierra->vx;
    vyt=Tierra->vy;

    xv=Venus->getPosx();
    yv=Venus->getPosy();
    vxv=Venus->vx;
    vyv=Venus->vy;

    xm=Marte->getPosx();
    ym=Marte->getPosy();
    vxm=Marte->vx;
    vym=Marte->vy;

    xj=Jupiter->getPosx();
    yj=Jupiter->getPosy();
    vxj=Jupiter->vx;
    vyj=Jupiter->vy;

    xu=Urano->getPosx();
    yu=Urano->getPosy();
    vxu=Urano->vx;
    vyu=Urano->vy;

    xs=sol->getPosx();
    ys=sol->getPosy();

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::nuevoy(int y)
{
    return 300-y;
}

int MainWindow::velocidad(int mi)
{

}

void MainWindow::on_pushButton_clicked()
{
    if(band) time->start(int(T*1000));
    else time->stop();
    band=!band;
}
void MainWindow::simulacion()
{

    //Para Venus
    r=sqrt(pow((xs-xv),2)+pow((ys-yv),2));
    r1=sqrt(pow((xm-xv),2)+pow((ym-yv),2));
    r2=sqrt(pow((xu-xv),2)+pow((yu-yv),2));
    r3=sqrt(pow((xt-xv),2)+pow((yt-yv),2));
    r4=sqrt(pow((xj-xv),2)+pow((yj-yv),2));

    ax=G*(((sol->masa*(xs-xv))/pow(r,3))+((Marte->masa*(xm-xv))/pow(r1,3))+((Urano->masa*(xu-xv))/pow(r2,3))+((Tierra->masa*(xt-xv))/pow(r3,3))+((Jupiter->masa*(xj-xv))/pow(r4,3)));
    ay=G*(((sol->masa*(ys-yv))/pow(r,3))+((Marte->masa*(ym-yv))/pow(r1,3))+((Urano->masa*(yu-yv))/pow(r2,3))+((Tierra->masa*(yt-yv))/pow(r3,3))+((Jupiter->masa*(yj-yv))/pow(r4,3)));
    vxv+=ax*T;
    vyv+=ay*T;
    xv+=vxv*T;
    yv+=vyv*T;
    Venus->setPosx((xv/20)+425);
    Venus->setPosy(nuevoy(int(yv/20)));
    Venus->setPos((xv/20)+425,nuevoy(int(yv/20)));

    //Para Tierra
    r=sqrt(pow((xs-xt),2)+pow((ys-yt),2));
    r1=sqrt(pow((xm-xt),2)+pow((ym-yt),2));
    r2=sqrt(pow((xu-xt),2)+pow((yu-yt),2));
    r3=sqrt(pow((xv-xt),2)+pow((yv-yt),2));
    r4=sqrt(pow((xj-xt),2)+pow((yj-yt),2));

    ax=G*(((sol->masa*(xs-xt))/pow(r,3))+((Marte->masa*(xm-xt))/pow(r1,3))+((Urano->masa*(xu-xt))/pow(r2,3))+((Venus->masa*(xv-xt))/pow(r3,3))+((Jupiter->masa*(xj-xt))/pow(r4,3)));
    ay=G*(((sol->masa*(ys-yt))/pow(r,3))+((Marte->masa*(ym-yt))/pow(r1,3))+((Urano->masa*(yu-yt))/pow(r2,3))+((Venus->masa*(yv-yt))/pow(r3,3))+((Jupiter->masa*(yj-yt))/pow(r4,3)));
    vxt+=ax*T*h;
    vyt+=ay*T*h;
    xt+=vxt*T*h;
    yt+=vyt*T*h;
    Tierra->setPosx((xt/20)+425);
    Tierra->setPosy(nuevoy(int(yt/20)));
    Tierra->setPos((xt/20)+425,nuevoy(int(yt/20)));

    //para marte
    r=sqrt(pow((xs-xm),2)+pow((ys-ym),2));
    r1=sqrt(pow((xt-xm),2)+pow((yt-ym),2));
    r2=sqrt(pow((xu-xm),2)+pow((yu-ym),2));
    r3=sqrt(pow((xv-xm),2)+pow((yv-ym),2));
    r4=sqrt(pow((xj-xm),2)+pow((yj-ym),2));

    ax=G*(((sol->masa*(xs-xm))/pow(r,3))+((Tierra->masa*(xt-xm))/pow(r1,3))+((Urano->masa*(xu-xm))/pow(r2,3))+((Venus->masa*(xv-xm))/pow(r3,3))+((Jupiter->masa*(xj-xm))/pow(r4,3)));
    ay=G*(((sol->masa*(ys-ym))/pow(r,3))+((Tierra->masa*(yt-ym))/pow(r1,3))+((Urano->masa*(yu-ym))/pow(r2,3))+((Venus->masa*(yv-ym))/pow(r3,3))+((Jupiter->masa*(yj-ym))/pow(r4,3)));
    vxm+=ax*T;
    vym+=ay*T;
    xm+=vxm*T;
    ym+=vym*T;
    Marte->setPosx((xm/20)+425);
    Marte->setPosy(nuevoy(int(ym/20)));
    Marte->setPos((xm/20)+425,nuevoy(int(ym/20)));

    //Para Jupiter
    r=sqrt(pow((xs-xj),2)+pow((ys-yj),2));
    r1=sqrt(pow((xt-xj),2)+pow((yt-yj),2));
    r2=sqrt(pow((xu-xj),2)+pow((yu-yj),2));
    r3=sqrt(pow((xv-xj),2)+pow((yv-yj),2));
    r4=sqrt(pow((xm-xj),2)+pow((ym-yj),2));

    ax=G*(((sol->masa*(xs-xj))/pow(r,3))+((Tierra->masa*(xt-xj))/pow(r1,3))+((Urano->masa*(xu-xj))/pow(r2,3))+((Venus->masa*(xv-xj))/pow(r3,3))+((Marte->masa*(xm-xj))/pow(r4,3)));
    ay=G*(((sol->masa*(ys-yj))/pow(r,3))+((Tierra->masa*(yt-yj))/pow(r1,3))+((Urano->masa*(yu-yj))/pow(r2,3))+((Venus->masa*(yv-yj))/pow(r3,3))+((Marte->masa*(ym-yj))/pow(r4,3)));
    vxj+=ax*T;
    vyj+=ay*T;
    xj+=vxj*T;
    yj+=vyj*T;
    Jupiter->setPosx((xj/20)+425);
    Jupiter->setPosy(nuevoy(int(yj/20)));
    Jupiter->setPos((xj/20)+425,nuevoy(int(yj/20)));


    //Para Urano
    r=sqrt(pow((xs-xu),2)+pow((ys-yu),2));
    r1=sqrt(pow((xt-xu),2)+pow((yt-yu),2));
    r2=sqrt(pow((xm-xu),2)+pow((ym-yu),2));
    r3=sqrt(pow((xv-xu),2)+pow((yv-yu),2));
    r4=sqrt(pow((xj-xu),2)+pow((yj-yu),2));

    ax=G*(((sol->masa*(xs-xu))/pow(r,3))+((Tierra->masa*(xt-xu))/pow(r1,3))+((Marte->masa*(xm-xu))/pow(r2,3))+((Venus->masa*(xv-xu))/pow(r3,3))+((Jupiter->masa*(xj-xu))/pow(r4,3)));
    ay=G*(((sol->masa*(ys-yu))/pow(r,3))+((Tierra->masa*(yt-yu))/pow(r1,3))+((Marte->masa*(ym-yu))/pow(r2,3))+((Venus->masa*(yv-yu))/pow(r3,3))+((Jupiter->masa*(yj-yu))/pow(r4,3)));
    vxu+=ax*T*h;
    vyu+=ay*T*h;
    xu+=vxu*T*h;
    yu+=vyu*T*h;
    Urano->setPosx((xu/20)+425);
    Urano->setPosy(nuevoy(int(yu/20)));
    Urano->setPos((xu/20)+425,nuevoy(int(yu/20)));
}

void MainWindow::on_lineEdit_inputRejected()
{

}
