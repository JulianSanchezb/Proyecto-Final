#include "jefe.h"
#include "jugador.h"
#include <QLineF>
#include <cmath>
using namespace std;

jefe::jefe(unsigned short int salu, int gravedad, int tiempo, unsigned short int anchoi,
           unsigned short int altoi, int posix, int posiy, int velox, int veloy,obstaculos* proyectiles) {
    salud = salu;
    g = gravedad;
    t = tiempo;
    ancho = anchoi;
    alto = altoi;
    onGround = true;
    pos = QPointF(posix,posiy);
    posx = posix;
    posy = posiy;
    velx = velox;
    vely = veloy;
}

void jefe::ataqueBasico(){
    if(colision()){
        int saludgoku = Goku->GetSalud - 5;
        Goku->SetSalud(saludgoku);
    }
}

void jefe::explosion() {

    float danioMax = 30.0;
    float epsilon = 2.0;

    QPointF miPos = pos;
    QPointF objetivoPos = Goku->GetPosicion();

    float distancia = QLineF(miPos, objetivoPos).length();

    int danio = danioMax / pow(distancia + epsilon, 2);
    int saludgoku = Goku->GetSalud - danio;
    Goku->SetSalud(saludgoku);
}

bool jefe::colision(){
    if(collidesWithItem(Goku)){
        return true;
    }else{
        return false;
    }
}


