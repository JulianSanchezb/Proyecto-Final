#ifndef JEFE_H
#define JEFE_H
#include "personaje.h"

class jugador;

class jefe : public personaje
{
private:
    jugador* Goku;
    QPointF pos;
public:
    jefe(unsigned short salu, int gravedad, int tiempo, unsigned short ancho, unsigned short alto,
         int posix, int posiy, int velox, int veloy, obstaculos *proyectiles);
    void ataqueBasico();
    void explosion();
    bool colision();

};

#endif // JEFE_H
