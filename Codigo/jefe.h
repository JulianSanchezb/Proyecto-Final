#ifndef JEFE_H
#define JEFE_H
#include "personaje.h"

class jugador;

class jefe : public personaje
{
private:
    jugador* Goku;
    QTimer* animTimer;
    QTimer* Timersecond;
    QTimer* Timerbasic;
    bool bandera = false;
    void moveUp();
    void moveRight();
    void moveLeft();
    //QPointF pos;
public:
    jefe(unsigned short salu, int gravedad, int tiempo, unsigned short ancho, unsigned short alto,
         int posix, int posiy, int velox, int veloy, jugador *goku);
    void ataqueBasico();
    void explosion();
    bool colision();
    void updateSprite();
};

#endif // JEFE_H
