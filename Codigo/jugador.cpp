#include "jugador.h"
#include "jefe.h"
#include "obstaculos.h"

jugador::jugador(short int salu, float gravedad, float tiempo, unsigned short int anchoi,unsigned short int altoi, float posix, float posiy, float velox, float veloy) {
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
    saludables = 0;
    energia = 0;
    guilan = nullptr;
}

void jugador::moveUp2(){
    posy -= vely;
    setPos(posx, posy);
}

void jugador::moveDown() {
    posy += vely;
    setPos(posx, posy);
}

void jugador::ataqueEpecial(){

}

void jugador::ataqueBasico(){
    short int saludGuilan = guilan->getSalud();
    if(colision()){
        saludGuilan = saludGuilan - 3;
        guilan->setSalud(saludGuilan);
    }
}

void jugador::consumir(unsigned short int tipo){
    switch(tipo){
    case 1:
        if (saludables != 0){
            short int saludGoku = this->getSalud();
            this->setSalud(saludGoku + 20);
            saludables = saludables - 1;
        }
        break;
    }
}

bool jugador::colision(){
    if(collidesWithItem(guilan)){
        return true;
    }else{
        return false;
    }
}
