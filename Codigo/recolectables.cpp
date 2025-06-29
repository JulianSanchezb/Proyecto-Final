#include "recolectables.h"

recolectables::recolectables() {}

QRectF recolectables::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void recolectables::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    //painter->setBrush(color); // usar el color actual
    painter->drawEllipse(0, 0, ancho, alto); // dibujo simple del fantasma
}
