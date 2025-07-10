#include "personaje.h"

personaje::personaje() {}

void personaje::moveUp() {
    velx = 0;

    vely += g;

    posx += velx;
    posy += vely;

    // Colisión con el suelo
    if (posy >= 560) {
        posy = 560;
        vely = 0;
        onGround = true;
    } else {
        onGround = false;
    }
    this->setPos(posx, posy);
}

void personaje::moveRight(){
    posx += velx;
    setPos(posx, posy);
}

void personaje::moveLeft(){
    posx -= velx;
    setPos(posx, posy);
}


//Getters
short int personaje::getSalud(){
    return salud;
}

float personaje::getPosx(){
    return posx;
}

float personaje::getPosy(){
    return posy;
}

float personaje::getGravedad(){
    return g;
}

unsigned short int personaje::getAncho(){
    return ancho;
}

unsigned short int personaje::getAlto(){
    return alto;
}

float personaje::getTiempo(){
    return t;
}

bool personaje::getGround(){
    return onGround;
}

//Setters
void personaje::setSalud(short int s){
    salud = s;
}

void personaje::setPosx(float x){
    posx =x;
}

void personaje::setPosy(float y){
    posy = y;
}

void personaje::setVelx(float x){
    velx =x;
}

void personaje::setVely(float y){
    vely =y;
}

void personaje::setGravedad(float gr){
    g = gr;
}

void personaje::setAncho(unsigned short int an){
    ancho = an;
}

void personaje::setAlto(unsigned short int al){
    alto = al;
}

void personaje::setTiempo(float tiempo){
    t = tiempo;
}

void personaje::setGround(bool ground){
    onGround = ground;
}
