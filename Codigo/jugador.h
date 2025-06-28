#ifndef JUGADOR_H
#define JUGADOR_H
#include "personaje.h"

class jugador : public personaje
{
private:
    int energia;
public:
    jugador();
    void moveUp2();
    void ataqueEpecial();
    void ataqueBasico();
};

#endif // JUGADOR_H
