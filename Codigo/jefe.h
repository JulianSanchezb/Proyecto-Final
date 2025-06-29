#ifndef JEFE_H
#define JEFE_H
#include "personaje.h"

class jugador;

class jefe : public personaje
{
private:
    jugador *goku;
public:
    jefe();
    void ataqueBasico();
    void ataqueDoppler();
};

#endif // JEFE_H
