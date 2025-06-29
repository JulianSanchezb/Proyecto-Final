#ifndef JUGADOR_H
#define JUGADOR_H
#include "personaje.h"

class jefe;

class jugador : public personaje
{
private:
    jefe *guilan;
    unsigned short int energia;
    unsigned short int saludables;
public:
    jugador();
    void moveUp2();
    void moveDown();
    void ataqueEpecial();
    void ataqueBasico();
    void consumir();
};

#endif // JUGADOR_H
