#include "personaje.h"

personaje::personaje() {}

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
