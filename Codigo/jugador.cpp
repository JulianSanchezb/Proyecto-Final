#include "jugador.h"
#include "jefe.h"

jugador::jugador(){}

void jugador::moveUp2(){
    posy -= vely;
    setPos(posx, posy);
}

void jugador::moveDown() {
    posy += vely;
    setPos(posx, posy);
}

void jugador::ataqueEpecial(){}

void jugador::ataqueBasico(){}

void jugador::consumir(){}
