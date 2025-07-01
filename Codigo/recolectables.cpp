#include "recolectables.h"

recolectables::recolectables() {}

QRectF recolectables::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}


