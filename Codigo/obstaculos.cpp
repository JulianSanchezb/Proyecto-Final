#include "obstaculos.h"

obstaculos::obstaculos() {}

void obstaculos::moveSenoidal() {
    //posy -= vel;
    setPos(posx, posy);
}

void obstaculos::moveParabolico() {
    //posy += vel;
    setPos(posx, posy);
}

void obstaculos::moveRecto() {
    //posx += vel;
    setPos(posx, posy);
}

QRectF obstaculos::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void obstaculos::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    //painter->setBrush(color); // usar el color actual
    painter->drawEllipse(0, 0, ancho, alto); // dibujo simple del fantasma
}
