#include "personaje.h"

personaje::personaje() {}

void personaje::moveUp() {
    posy -= vely;
    setPos(posx, posy);
}

void personaje::moveRight() {
    posx += velx;
    setPos(posx, posy);
}

void personaje::moveLeft() {
    posx -= velx;
    setPos(posx, posy);
}

QRectF personaje::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
   //painter->setBrush(color); // usar el color actual
    painter->drawEllipse(0, 0, ancho, alto); // dibujo simple del fantasma
}

void personaje::setPosy(int y){
    posy -= y;
}
