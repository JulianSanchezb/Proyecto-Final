#ifndef NIVEL2_H
#define NIVEL2_H
#include <QGraphicsScene>
class obstaculos;
class jugador;
class jefe;
class recolectables;

class nivel2
{
    QGraphicsScene *scene;
public:
    nivel2();
    QVector<QPixmap> sprites;
    QVector<obstaculos*> proyectil;
    jugador* Goku;
    jefe* Giran;
};

#endif // NIVEL2_H
