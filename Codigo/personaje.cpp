#include "personaje.h"

personaje::personaje() {}

void personaje::moveup() {
    posy -= vel;
    setPos(posx, posy);
}

void personaje::movedown() {
    posy += vel;
    setPos(posx, posy);
}

void personaje::moveright() {
    posx += vel;
    setPos(posx, posy);
}

void personaje::moveleft() {
    posx -= vel;
    setPos(posx, posy);
}

QRectF personaje::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color); // usar el color actual
    painter->drawEllipse(0, 0, ancho, alto); // dibujo simple del fantasma
}
