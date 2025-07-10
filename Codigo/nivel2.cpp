#include "nivel2.h"
#include "obstaculos.h"
#include "jugador.h"
#include "jefe.h"

nivel2::nivel2(jugador *goku): scene(new QGraphicsScene()),
    Goku(goku),
    Giran(new jefe(700, 1.5, 0, 100, 70, 4, 180, 10, 5, Goku)),
    timerP(new QTimer(this))
{
    creacion(proyectiles,3,3);
    creacion(esferas,1,5);

    QPixmap img(":/Multimedia/arena.png");
    scene->setBackgroundBrush(img);
    scene->setSceneRect(img.rect());


    QPixmap salud(":/Multimedia/salud.png");
    QPixmap saludEscalada = salud.scaled(95,62);
    QGraphicsPixmapItem* vida = scene->addPixmap(saludEscalada);
    vida->setPos(423,-10);
    vida->setZValue(10);

    QPixmap saludE = salud.scaled(125,102);
    QGraphicsPixmapItem* vidaGiran = scene->addPixmap(saludE);
    vidaGiran->setPos(0,-25);
    vidaGiran->setZValue(10);

    QPixmap imgEsfera(":/Multimedia/esfera1.png");
    QGraphicsPixmapItem* esfera = scene->addPixmap(imgEsfera);
    esfera->setPos(390, 3);
    esfera->setScale(0.5);
    esfera->setZValue(20);

    // Leche decorativa
    QPixmap imgLeche(":/Multimedia/leche.png");
    QGraphicsPixmapItem* leche = scene->addPixmap(imgLeche);
    leche->setPos(360, 3);
    leche->setScale(0.5);
    leche->setZValue(20);

    t1 = new QGraphicsTextItem;
    scene->addItem(t1);
    t1->setPos(377, 5);
    t1->setScale(0.9);
    t1->setPlainText(QString::number(Goku->getSaludables()));

    t2 = new QGraphicsTextItem;
    scene->addItem(t2);
    t2->setPos(413, 5);
    t2->setScale(0.9);
    t2->setPlainText(QString::number(Goku->getEnergia()));

    barraSalud = new QProgressBar();
    barraSalud->setRange(0, 500);
    barraSalud->setTextVisible(0);

    barraSalud->setStyleSheet(
        "QProgressBar {"
        "  border: 2px solid transparent;"
        "  border-radius: 1px;"
        "  text-align: center;"
        "  background-color: transparent;"
        "}"
        "QProgressBar::chunk {"
        "  background-color: red;"
        "  width: 2px;"
        "}"
        );

    barraSalud->setValue(Goku->getSalud());
    barraSalud->setFixedSize(63,11);

    proxy1 = scene->addWidget(barraSalud);
    proxy1->setZValue(11);
    proxy1->setPos(445,18);

    barraGiran = new QProgressBar();
    barraGiran->setRange(0, 700);
    barraGiran->setTextVisible(0);

    barraGiran->setStyleSheet(
        "QProgressBar {"
        "  border: 2px solid transparent;"
        "  border-radius: 1px;"
        "  text-align: center;"
        "  background-color: transparent;"
        "}"
        "QProgressBar::chunk {"
        "  background-color: #a8b850;"
        "  width: 2px;"
        "}"
        );

    barraGiran->setValue(Giran->getSalud());
    barraGiran->setFixedSize(87,14);

    proxy2 = scene->addWidget(barraGiran);
    proxy2->setZValue(11);
    proxy2->setPos(29,23);

    scene->addItem(Goku);
    Goku->setPos(370,200);
    Goku->setScale(0.5);
    Goku->setGuilan(Giran);

    scene->addItem(Giran);
    Giran->setPos(4,180);
    Giran->setScale(0.5);


    connect(timerP, &QTimer::timeout, this, [=]() {
        if(Giran){
            if(Giran->x() >= 390 && Giran->x() <= 430){
                mostrar_obstaculo(proyectiles, 3, 50, 20,-1,1);
            }else if(Giran->x()<=10 && Giran->x() >= 1){
                mostrar_obstaculo(proyectiles, 3, 50, 20,1,1);
            }
        }
        if(Goku->especial && Goku->getEnergia() > 0 && variable == true){
            variable = false;
            mostrar_obstaculo(esferas,1,50,20,Goku->getdireccion(),0);
            QTimer::singleShot(1000, this, [=]() {
                variable = true;
            });
        }
        barraSalud->setValue(Goku->getSalud());
        if(Giran){
          barraGiran->setValue(Giran->getSalud());
        }
    });
    timerP->start(200);
}

nivel2::~nivel2() {
    if (timerP) {
        timerP->stop();
        delete timerP;
        timerP = nullptr;
    }

    if (proxy1) {
        delete proxy1;
        proxy1 = nullptr;
    }

    if (proxy2) {
        delete proxy2;
        proxy2 = nullptr;
    }

    if (t1) {
        delete t1;
        t1 = nullptr;
    }

    if (t2) {
        delete t2;
        t2 = nullptr;
    }
    if (Giran) {
        delete Giran;
        Giran = nullptr;
    }
    if(Goku->scene()){
        scene->removeItem(Goku);
    }
    if (scene) {
        scene->clear();
        delete scene;
        scene = nullptr;
    }

}

void nivel2::mostrar_obstaculo(QVector<obstaculos *>& contenedor, int cantidad,
                               int x, int y, int direccion,bool tipo) {
    QPointF posicion = QPointF(x,y);
    QPointF inicio;

    if(tipo){
        inicio = Giran->pos();
    }else{
        inicio = Goku->pos();
    }
    for (int i = 0; i < cantidad; ++i) {
        if (!contenedor[i]->getdisponible()){
            QPointF origen = inicio  + posicion;
            contenedor[i]->activar(origen,100);
            contenedor[i]->direccion = direccion;
            break;
        }
    }
}

void nivel2::creacion(QVector<obstaculos*>& contenedor, int cantidad, unsigned short int tipo) {
    for (int i = 0; i < cantidad; ++i) {
        obstaculos* obj = new obstaculos(0, 0, 0, 0, 0, -1.5, 15, 15, Goku, tipo);
        contenedor.append(obj);
        scene->addItem(obj);
        obj->desactivar();
        if(tipo == 5){
            obj->setGuiran(Giran);
        }
    }
}

//getter
QGraphicsScene* nivel2::obtenerEscena(){
    return scene;
}

jugador* nivel2::getGoku(){
    return Goku;
}

jefe* nivel2::getGiran(){
    return Giran;
}

//setter
void nivel2::setGoku(jugador* goku){
    Goku = goku;
}

void nivel2::setT1(){
    t1->setPlainText(QString::number(Goku->getSaludables()));
}

void nivel2::setT2(){
    t2->setPlainText(QString::number(Goku->getEnergia()));
}


