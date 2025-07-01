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
    QVector<obstaculos*> balas;
    QVector<obstaculos*> pajaros;
public:
    nivel1();
    QVector<QPixmap> sprites;
    QList<recolectables*> recursos;
    jugador* Goku;
    jefe* camara;
    void creacion(QVector<obstaculos*>& contenedor, int cantidad, unsigned short int tipo);
    void dispararBala();

};

#endif // NIVEL1_H
