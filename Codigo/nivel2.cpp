#include "nivel2.h"
#include "jefe.h"
#include "jugador.h"
#include "obstaculos.h"

nivel2::nivel2(jugador *goku): scene(new QGraphicsScene()),
    Goku(goku),
    Giran(new jefe(250, 1.5, 0, 100, 70, 4, 180, 5, 5, Goku)),
    timerP(new QTimer(this))
{
    creacion(proyectiles,3,3);
    creacion(esferas,1,4);

    QPixmap img(":/Multimedia/arena.png");
    scene->setBackgroundBrush(img);
    scene->setSceneRect(img.rect());


    QPixmap salud(":/Multimedia/salud.png");
    QPixmap saludEscalada = salud.scaled(88,63);  // Aquí sí se guarda la imagen escalada
    QGraphicsPixmapItem* vida = scene->addPixmap(saludEscalada);
    vida->setPos(430,-8); // Posición exacta en la escena
    vida->setZValue(10);

    QPixmap imgEsfera(":/Multimedia/esfera1.png");
    QGraphicsPixmapItem* esfera = scene->addPixmap(imgEsfera);
    esfera->setPos(390, 3);
    esfera->setScale(0.5);  // si es muy grande
    esfera->setZValue(20);   // encima del fondo pero debajo de personajes si quieres

    // Leche decorativa
    QPixmap imgLeche(":/Multimedia/leche.png");
    QGraphicsPixmapItem* leche = scene->addPixmap(imgLeche);
    leche->setPos(360, 3);
    leche->setScale(0.5);
    leche->setZValue(20);

    scene->addItem(Goku);
    Goku->setPos(370,200);
    Goku->setScale(0.5);

    scene->addItem(Giran);
    Giran->setPos(4,180);
    Giran->setScale(0.5);

    qDebug()<<Goku->pos();
    connect(timerP, &QTimer::timeout, this, [=]() {
        if(Giran->x() >= 390 && Giran->x() <= 430){
            mostrar_obstaculo(proyectiles, 3, 50, 20,-1,1);
        }else if(Giran->x()<=10 && Giran->x() >= 1){
            mostrar_obstaculo(proyectiles, 3, 50, 20,1,1);
        }
        if(Goku->especial && Goku->getEnergia() > 0){
             mostrar_obstaculo(esferas,1,50,20,Goku->getdireccion(),0);
        }
    });
    timerP->start(500);



}

void nivel2::mostrar_obstaculo(QVector<obstaculos *>& contenedor, int cantidad,
                               int x, int y, int direccion,bool tipo) {// puede ser plantilla para pajaros y balas.
    QPointF posicion = QPointF(x,y);
    QPointF inicio;

    if(tipo){
        inicio = Giran->pos();
    }else{
        inicio = Goku->pos();
    }
    for (int i = 0; i < cantidad; ++i) {
        if (!contenedor[i]->getdisponible()){
            QPointF origen = inicio  + posicion;  // punto desde donde sale la bala, modificar 200 y 50
            contenedor[i]->activar(origen,100);// para QpointF puede pasarse como parametro para que funicone para pajaros tambien
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
    }
}


//getter
QGraphicsScene* nivel2::obtenerEscena(){
    return scene;
}

jugador* nivel2::getGoku(){
    return Goku;
}


//setter
void nivel2::setGoku(jugador* goku){
    Goku = goku;
}


