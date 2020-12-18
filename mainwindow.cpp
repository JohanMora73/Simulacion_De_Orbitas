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
    contador=0;
    /*sol=new Planeta(0,0,70000,300,0,0,Qt::yellow);
    Urano=new Planeta(4000,5000,25,100,-1.6,1.2,Qt::cyan);
    Venus=new Planeta(1,1,0,1,0,0,Qt::magenta);
    Tierra=new Planeta(0,-7000,70,120,2,0,Qt::green);
    Marte=new Planeta(0,-5000,0,70,0,0,Qt::red);
    Jupiter=new Planeta(0,5000,0,70,0,0,Qt::gray);*/
    px = new double[6];
    py = new double[6];
    Vx = new double[6];
    Vy = new double[6];
    //planetas<<sol<<Urano<<Venus<<Tierra<<Marte<<Jupiter;
    scene->setBackgroundBrush(QPixmap(":/imagenes/fondodeff.jpg"));
    ui->graphicsView->setScene(scene);
    connect(time,SIGNAL(timeout()),this,SLOT(simulacion()));

    /*xt=Tierra->getPosx(); yt=Tierra->getPosy(); vxt=Tierra->vx; vyt=Tierra->vy;
    xv=Venus->getPosx(); yv=Venus->getPosy(); vxv=Venus->vx; vyv=Venus->vy;
    xm=Marte->getPosx(); ym=Marte->getPosy(); vxm=Marte->vx; vym=Marte->vy;
    xj=Jupiter->getPosx(); yj=Jupiter->getPosy(); vxj=Jupiter->vx; vyj=Jupiter->vy;
    xu=Urano->getPosx(); yu=Urano->getPosy(); vxu=Urano->vx; vyu=Urano->vy;
    xs=sol->getPosx(); ys=sol->getPosy(); vxs=sol->vx; vys=sol->vy;
    */
    /*
    px[0]=xs; px[1]=xu; px[2]=xv; px[3]=xt; px[4]=xm; px[5]=xj;
    py[0]=ys; py[1]=yu; py[2]=yv; py[3]=yt; py[4]=ym; py[5]=yj;
    Vx[0]=vxs; Vx[1]=vxu; Vx[2]=vxv; Vx[3]=vxt; Vx[4]=vxm; Vx[5]=vxj;
    Vy[0]=vys; Vx[1]=vyu; Vx[2]=vyv; Vx[3]=vyt; Vx[4]=vym; Vx[5]=vyj;
*/
    Escribir1();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::nuevoy(int y)
{
    return 300-y;
}

void MainWindow::MostrarPlanetas(int num)
{
    int cont=0;
    for (it=planetas.begin();it!=planetas.end() ;it++ ) {
        if(cont<num){
            scene->addItem(*it);
            cont++;
        }
        else{
            scene->removeItem(*it);
        }
    }
}

void MainWindow::Escribir()
{
    ofstream archivo;
    archivo.open("simulacion.txt",ios::app);//abriendo el archivo en modo añadir texto

    if (archivo.fail()) exit(1);

    archivo<<xs<<"   "<<ys<<"    "<<xv<<"    "<<yv<<"    "<<xt<<"    "<<yt<<"    "<<xm<<"    "<<ym<<"    "<<xj<<"    "<<yj<<"   "<<xu<<"    "<<yu<<'\n';//"ax: "<<ax<<" ay: "<<ay<<'\n';
    archivo.close();
}

void MainWindow::Escribir1()
{
    ofstream archivo;
    archivo.open("simulacion.txt",ios::out);//abriendo el archivo en modo añadir texto

    if (archivo.fail()) exit(1);

    //archivo<<xs<<"   "<<ys<<"   "<<xu<<"    "<<yu<<"    "<<xv<<"    "<<yv<<"    "<<xt<<"    "<<yt<<"    "<<xm<<"    "<<ym<<"    "<<xj<<"    "<<yj<<'\n';//"ax: "<<ax<<" ay: "<<ay<<'\n';
    archivo<<"   Sol x:      Sol y:     Venus x:    Venus y:    Tierra x:    Tierra y:       Marte x:       Marte y:       Jupiter x:     Jupiter y:     Urano x:    Urano y:"<<'\n';//"ax: "<<ax<<" ay: "<<ay<<'\n';
    archivo.close();
}

void MainWindow::on_pushButton_clicked()
{
    if(band) time->start(int(T*1000));
    QString num_ = ui->spinBox->text();
    num=num_.toInt();
    //ui->label->setText(QString::number(num));
    //ui->label_2->setText(QString::number(sol->posx));
    MostrarPlanetas(num);
    //else time->stop();
    band=!band;
}

void MainWindow::simulacion()
{
    //Para el sol
    r=sqrt(pow((xu-xs),2)+pow((yu-ys),2));
    r1=sqrt(pow((xt-xs),2)+pow((yt-ys),2));
    r2=sqrt(pow((xm-xs),2)+pow((ym-ys),2));
    r3=sqrt(pow((xv-xs),2)+pow((yv-ys),2));
    r4=sqrt(pow((xj-xs),2)+pow((yj-ys),2));

    ax=G*(((Urano->masa*(xu-xs))/pow(r,3))+((Tierra->masa*(xt-xs))/pow(r1,3))+((Marte->masa*(xm-xs))/pow(r2,3))+((Venus->masa*(xv-xs))/pow(r3,3))+((Jupiter->masa*(xj-xs))/pow(r4,3)));
    ay=G*(((Urano->masa*(yu-ys))/pow(r,3))+((Tierra->masa*(yt-ys))/pow(r1,3))+((Marte->masa*(ym-ys))/pow(r2,3))+((Venus->masa*(yv-ys))/pow(r3,3))+((Jupiter->masa*(yj-ys))/pow(r4,3)));
    vxs+=ax*T*h;
    vys+=ay*T*h;
    xs+=vxs*T*h;
    ys+=vys*T*h;
    sol->setPosx((xs/25)+425);
    sol->setPosy(nuevoy(int(ys/25)));
    sol->setPos((xs/25)+425,nuevoy(int(ys/25)));

    //Para Venus
    r=sqrt(pow((xs-xv),2)+pow((ys-yv),2));
    r1=sqrt(pow((xm-xv),2)+pow((ym-yv),2));
    r2=sqrt(pow((xu-xv),2)+pow((yu-yv),2));
    r3=sqrt(pow((xt-xv),2)+pow((yt-yv),2));
    r4=sqrt(pow((xj-xv),2)+pow((yj-yv),2));

    ax=G*(((sol->masa*(xs-xv))/pow(r,3))+((Marte->masa*(xm-xv))/pow(r1,3))+((Urano->masa*(xu-xv))/pow(r2,3))+((Tierra->masa*(xt-xv))/pow(r3,3))+((Jupiter->masa*(xj-xv))/pow(r4,3)));
    ay=G*(((sol->masa*(ys-yv))/pow(r,3))+((Marte->masa*(ym-yv))/pow(r1,3))+((Urano->masa*(yu-yv))/pow(r2,3))+((Tierra->masa*(yt-yv))/pow(r3,3))+((Jupiter->masa*(yj-yv))/pow(r4,3)));
    vxv+=ax*T*h;
    vyv+=ay*T*h;
    xv+=vxv*T*h;
    yv+=vyv*T*h;
    Venus->setPosx((xv/25)+425);
    Venus->setPosy(nuevoy(int(yv/25)));
    Venus->setPos((xv/25)+425,nuevoy(int(yv/25)));

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
    Tierra->setPosx((xt/25)+425);
    Tierra->setPosy(nuevoy(int(yt/25)));
    Tierra->setPos((xt/25)+425,nuevoy(int(yt/25)));

    //para marte
    r=sqrt(pow((xs-xm),2)+pow((ys-ym),2));
    r1=sqrt(pow((xt-xm),2)+pow((yt-ym),2));
    r2=sqrt(pow((xu-xm),2)+pow((yu-ym),2));
    r3=sqrt(pow((xv-xm),2)+pow((yv-ym),2));
    r4=sqrt(pow((xj-xm),2)+pow((yj-ym),2));

    ax=G*(((sol->masa*(xs-xm))/pow(r,3))+((Tierra->masa*(xt-xm))/pow(r1,3))+((Urano->masa*(xu-xm))/pow(r2,3))+((Venus->masa*(xv-xm))/pow(r3,3))+((Jupiter->masa*(xj-xm))/pow(r4,3)));
    ay=G*(((sol->masa*(ys-ym))/pow(r,3))+((Tierra->masa*(yt-ym))/pow(r1,3))+((Urano->masa*(yu-ym))/pow(r2,3))+((Venus->masa*(yv-ym))/pow(r3,3))+((Jupiter->masa*(yj-ym))/pow(r4,3)));
    vxm+=ax*T*h;
    vym+=ay*T*h;
    xm+=vxm*T*h;
    ym+=vym*T*h;
    Marte->setPosx((xm/25)+425);
    Marte->setPosy(nuevoy(int(ym/25)));
    Marte->setPos((xm/25)+425,nuevoy(int(ym/25)));

    //Para Jupiter
    r=sqrt(pow((xs-xj),2)+pow((ys-yj),2));
    r1=sqrt(pow((xt-xj),2)+pow((yt-yj),2));
    r2=sqrt(pow((xu-xj),2)+pow((yu-yj),2));
    r3=sqrt(pow((xv-xj),2)+pow((yv-yj),2));
    r4=sqrt(pow((xm-xj),2)+pow((ym-yj),2));

    ax=G*(((sol->masa*(xs-xj))/pow(r,3))+((Tierra->masa*(xt-xj))/pow(r1,3))+((Urano->masa*(xu-xj))/pow(r2,3))+((Venus->masa*(xv-xj))/pow(r3,3))+((Marte->masa*(xm-xj))/pow(r4,3)));
    ay=G*(((sol->masa*(ys-yj))/pow(r,3))+((Tierra->masa*(yt-yj))/pow(r1,3))+((Urano->masa*(yu-yj))/pow(r2,3))+((Venus->masa*(yv-yj))/pow(r3,3))+((Marte->masa*(ym-yj))/pow(r4,3)));
    vxj+=ax*T*h;
    vyj+=ay*T*h;
    xj+=vxj*T*h;
    yj+=vyj*T*h;
    Jupiter->setPosx((xj/25)+425);
    Jupiter->setPosy(nuevoy(int(yj/25)));
    Jupiter->setPos((xj/25)+425,nuevoy(int(yj/25)));


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
    Urano->setPosx((xu/25)+425);
    Urano->setPosy(nuevoy(int(yu/25)));
    Urano->setPos((xu/25)+425,nuevoy(int(yu/25)));

    Escribir();
}



/*
void MainWindow::simulacion()
{

    //int i=0;
    //for (it=planetas.begin();it!=planetas.end();it++){
      //  ax=0;ay=0;
       // int j=0;
        //for (it2=planetas.begin();it2!=planetas.end();it2++) {
          //  if(it!=it2){
            //    r=sqrt(pow(px[i]-px[j],2)+pow(py[i]-py[j],2));
              //  ax+=((G*it->masa))*(px[i]-px[j]))/r;
            //}
       // }
    //}
    //Escribir(ax,ay);
    for(int i=0;i<=6;i++){
        ax=0;ay=0;
        for(int j=0;j<=6;j++){
            if(i != j){
                r=sqrt(pow(px[i]-px[j],2)+pow(py[i]-py[j],2));
                ax+=((G*planetas[j]->masa)*(px[j]-px[i]))/r;
                ay+=((G*planetas[j]->masa)*(py[j]-py[i]))/r;
            }
        }
        Vx[i]+=ax*T*h;
        Vy[i]+=ay*T*h;
        px[i]+=Vx[i]*T*h;
        py[i]+=Vy[i]*T*h;
        planetas[i]->setPosx((px[i]/20)+425);
        planetas[i]->setPosy(nuevoy(int(py[i]/20)));
        planetas[i]->setPos((px[i]/20)+425,nuevoy(int(py[i]/20)));
    }
}
*/
void MainWindow::on_pushButton_2_clicked()
{
    if(contador==0){
        //sol->radio=ui->Radio_s->text().toDouble()*100;
        //int rs = int(ui->Radio_s->value()*100);
        //int ms = int(ui->Masa_s->value()*10000);
        //int rs=rs_.toDouble()*100;
        //int ms = ms_.toDouble()*10000; //int(ui->Masa_s->text().toDouble()*10000);
        //ui->label->setText(QString::number(rs));
        //ui->label_2->setText(QString::number(ms));

        /*
        sol=new Planeta(int(ui->xo_s->value()),int(ui->yo_s->value()),int(ui->Masa_s->value()),int(ui->Radio_s->value()),ui->Vox_s->value(),ui->Voy_s->value(),Qt::yellow);
        Urano=new Planeta(int(ui->xo_u->value()),int(ui->yo_u->value()),int(ui->Masa_u->value()),int(ui->Radio_u->value()),ui->Vox_u->value(),ui->Voy_u->value(),Qt::cyan);
        Venus=new Planeta(int(ui->xo_v->value()),int(ui->yo_v->value()),int(ui->Masa_v->value()),int(ui->Radio_v->value()),ui->Vox_v->value(),ui->Voy_v->value(),Qt::magenta);
        Tierra=new Planeta(int(ui->xo_t->value()),int(ui->yo_t->value()),int(ui->Masa_t->value()),int(ui->Radio_t->value()),ui->Vox_t->value(),ui->Voy_t->value(),Qt::green);
        Marte=new Planeta(int(ui->xo_m->value()),int(ui->yo_m->value()),int(ui->Masa_m->value()),int(ui->Radio_m->value()),ui->Vox_m->value(),ui->Voy_m->value(),Qt::red);
        Jupiter=new Planeta(int(ui->xo_j->value()),int(ui->yo_j->value()),int(ui->Masa_j->value()),int(ui->Radio_j->value()),ui->Vox_j->value(),ui->Voy_j->value(),Qt::gray);
        */

        sol=new Planeta(0,0,70000,300,0,0,Qt::yellow);
        Venus=new Planeta(0,-7000,70,120,2,0,Qt::magenta);
        Tierra=new Planeta(4000,5000,25,100,-1.6,1.2,Qt::green);
        Marte=new Planeta(1,0,0,1,0,0,Qt::red);
        Jupiter=new Planeta(2,0,0,1,0,0,Qt::gray);
        Urano=new Planeta(3,0,0,1,0,0,Qt::cyan);


        planetas<<sol<<Venus<<Tierra<<Marte<<Jupiter<<Urano;
        xt=Tierra->getPosx(); yt=Tierra->getPosy(); vxt=Tierra->vx; vyt=Tierra->vy;
        xv=Venus->getPosx(); yv=Venus->getPosy(); vxv=Venus->vx; vyv=Venus->vy;
        xm=Marte->getPosx(); ym=Marte->getPosy(); vxm=Marte->vx; vym=Marte->vy;
        xj=Jupiter->getPosx(); yj=Jupiter->getPosy(); vxj=Jupiter->vx; vyj=Jupiter->vy;
        xu=Urano->getPosx(); yu=Urano->getPosy(); vxu=Urano->vx; vyu=Urano->vy;
        xs=sol->getPosx(); ys=sol->getPosy(); vxs=sol->vx; vys=sol->vy;

        /*
        px[0]=xs; px[1]=xv; px[2]=xt; px[3]=xm; px[4]=xj; px[5]=xu;
        py[0]=ys; py[1]=yv; py[2]=yt; py[3]=ym; py[4]=yj; py[5]=yu;
        Vx[0]=vxs; Vx[1]=vxv; Vx[2]=vxt; Vx[3]=vxm; Vx[4]=vxj; Vx[5]=vxu;
        Vy[0]=vys; Vx[1]=vyv; Vx[2]=vyt; Vx[3]=vym; Vx[4]=vyj; Vx[5]=vyu;
        */
        contador+=1;
    }
}
