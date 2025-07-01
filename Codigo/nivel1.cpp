#include "nivel1.h"
#include "obstaculos.h"
#include "jugador.h"

nivel1::nivel1() {}

// hay que agregar todo a la escena
//revisar al final que va a ser camara
void nivel1::dispararBala() {// puede ser plantilla para pajaros y balas.
    for (obstaculos* bala : balas) {
        if (!bala->getdisponible()){
            QPointF origen = /*camara.pos*/ + QPointF(200, 50);  // punto desde donde sale la bala, modificar 200 y 50
            bala->activar(origen,30);// para QpointF puede pasarse como parametro para que funicone para pajaros tambien
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


