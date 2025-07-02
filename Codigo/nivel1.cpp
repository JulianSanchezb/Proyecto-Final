#include "nivel1.h"
#include "obstaculos.h"
#include "jugador.h"

nivel1::nivel1() {}

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


