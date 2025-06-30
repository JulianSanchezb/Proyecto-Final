#ifndef NIVEL1_H
#define NIVEL1_H
#include <QGraphicsScene>
class obstaculos;
class jugador;
class jefe;
class recolectables;

class nivel1
{
    QGraphicsScene *scene;
public:
    nivel1();
    QVector<QPixmap> sprites;
    QVector<obstaculos*> balas;
    QVector<obstaculos*> pajaros;
    QList<recolectables*> recursos;
    jugador* Goku;
    jefe* camara;
};

#endif // NIVEL1_H
