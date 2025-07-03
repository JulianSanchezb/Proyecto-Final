#include "nivel1.h"
#include "obstaculos.h"
#include "jugador.h"

nivel1::nivel1(): scene(new QGraphicsScene()),
    Goku(nullptr),
    camara(new obstaculos(100,1, 0, 1, 0, 0, 10, 10, Goku, 1))

{
    creacion(balas,3,4);
    creacion(pajaros,3,2);
    QPixmap img("C:/Users/Julian/Pictures/Saved Pictures/Sprites/Nivel 1B.jpg");
    QGraphicsPixmapItem* fondo = scene->addPixmap(img);
    fondo->setZValue(-1); // Para que quede al fondo
    scene->setSceneRect(img.rect());
    //camara->setScale(0.5);
    scene->addItem(camara);
    camara->setPos(100,1);
}

// hay que agregar todo a la escena
//revisar al final que va a ser camara


void nivel1::mostrar_obstaculo(QVector<obstaculos*> contenedor, int cantidad, int x, int y) {// puede ser plantilla para pajaros y balas.
    QPointF posicion = QPointF(x,y);
    for (int i = 0; i < cantidad; ++i) {
        if (!contenedor[i]->getdisponible()){
            QPointF origen = camara->pos() + posicion;  // punto desde donde sale la bala, modificar 200 y 50
            contenedor[i]->activar(origen,30);// para QpointF puede pasarse como parametro para que funicone para pajaros tambien
            break;
        }
    }
}

void nivel1::creacion(QVector<obstaculos*>& contenedor, int cantidad, unsigned short int tipo) {
    for (int i = 0; i < cantidad; ++i) {
        obstaculos* obj = new obstaculos(0, 0, 0, 0, 0, 0, 10, 10, Goku, tipo);
        obj->desactivar();
        contenedor.append(obj);
    }
}

QGraphicsScene* nivel1::obtenerEscena(){
    return scene;
}

//Setters
void nivel1::setGoku(jugador* goku){
    Goku = goku;
}


