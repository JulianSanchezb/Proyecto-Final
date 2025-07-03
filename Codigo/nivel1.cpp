#include "nivel1.h"
#include "obstaculos.h"
#include "jugador.h"

nivel1::nivel1(): scene(new QGraphicsScene()),
    Goku(nullptr),
    camara(new obstaculos(100,1, 0, 1, 0, 0, 20, 20, Goku, 1))

{
    creacion(balas,3,4);
    creacion(pajaros,2,2);
    QPixmap img(":/Multimedia/background-1.png");
    QGraphicsPixmapItem* fondo = scene->addPixmap(img);
    fondo->setZValue(-1); // Para que quede al fondo
    scene->setSceneRect(img.rect());

    crearNube(":/Multimedia/nubes.png",QPointF(1,1),1);

    scene->addItem(camara);
    camara->setPos(1,1);
    timerM = new QTimer(this);
    timerP = new QTimer(this);
    connect(timerM, &QTimer::timeout, this, [=]() {
        mostrar_obstaculo(balas, 3, 1, 2);
    });
    timerM->start(2000);
    connect(timerP, &QTimer::timeout, this, [=]() {
        mostrar_obstaculo(pajaros, 2, 1, 4);
    });
    timerP->start(4000);
}

// hay que agregar todo a la escena
//revisar al final que va a ser camara


void nivel1::mostrar_obstaculo(QVector<obstaculos*> contenedor, int cantidad, int x, int y) {// puede ser plantilla para pajaros y balas.
    QPointF posicion = QPointF(x,y);
    for (int i = 0; i < cantidad; ++i) {
        if (!contenedor[i]->getdisponible()){
            QPointF origen = camara->pos() + posicion;  // punto desde donde sale la bala, modificar 200 y 50
            contenedor[i]->activar(origen,200);// para QpointF puede pasarse como parametro para que funicone para pajaros tambien
            break;
        }
    }
}

void nivel1::creacion(QVector<obstaculos*>& contenedor, int cantidad, unsigned short int tipo) {
    for (int i = 0; i < cantidad; ++i) {
        obstaculos* obj = new obstaculos(0, 0, 0, 0, 0, 0, 15, 15, Goku, tipo);
        contenedor.append(obj);
        scene->addItem(obj);
        obj->desactivar();
    }
}

void nivel1::crearNube(const QString& rutaImagen, QPointF posicionInicial, float velocidad)
{
    // Crear nube con la imagen
    QPixmap pixmap(rutaImagen);
    QGraphicsPixmapItem* nube = scene->addPixmap(pixmap);
    nube->setPos(posicionInicial);
    nube->setZValue(-0.5); // Entre fondo y personajes

    // Crear temporizador para mover la nube
    QTimer* nubeTimer = new QTimer(this);
    connect(nubeTimer, &QTimer::timeout, this, [=]() {
        nube->moveBy(velocidad, 0);

        // Si sale de la escena por la derecha, vuelve a empezar por la izquierda
        if (nube->x() > 20) {
            nube->setX(-nube->boundingRect().width());
        }
    });

    nubeTimer->start(35); // Mover cada 30 ms
}



QGraphicsScene* nivel1::obtenerEscena(){
    return scene;
}

//Setters
void nivel1::setGoku(jugador* goku){
    Goku = goku;
}


