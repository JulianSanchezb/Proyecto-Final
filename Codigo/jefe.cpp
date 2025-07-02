#include "jefe.h"
#include "jugador.h"
#include <QLineF>
#include <cmath>
using namespace std;

jefe::jefe(unsigned short int salu, int gravedad, int tiempo, unsigned short int anchoi,
           unsigned short int altoi, int posix, int posiy, int velox, int veloy,jugador* goku) {
    setSalud(salu);
    setGravedad(gravedad);
    setTiempo(tiempo);
    setAncho(anchoi);
    setAlto(altoi);
    setGround(true);
    pos = QPointF(posix,posiy);
    posx = posix;
    posy = posiy;
    velx = velox;
    vely = veloy;
    Goku = goku;
}

void jefe::ataqueBasico(){
    if(colision()){
        int saludgoku = (Goku->getSalud()) - 5;
        Goku->setSalud(saludgoku);
    }
}

void jefe::explosion() {

    float danioMax = 30.0;
    float epsilon = 2.0;

    QPointF miPos = pos;
    QPointF objetivoPos = Goku->pos;

    float distancia = QLineF(miPos, objetivoPos).length();

    int danio = danioMax / pow(distancia + epsilon, 2);
    int saludgoku = (Goku->getSalud())- danio;
    Goku->setSalud(saludgoku);
}

bool jefe::colision(){
    if(collidesWithItem(Goku)){
        return true;
    }else{
        return false;
    }
}


