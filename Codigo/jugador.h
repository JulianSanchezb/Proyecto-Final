#ifndef JUGADOR_H
#define JUGADOR_H
#include "personaje.h"
#include <QTimer>

class jefe;

class jugador : public personaje
{
private:
    jefe *guilan;
    unsigned short int energia;
    unsigned short int saludables;
public:
    jugador(short int salu, float gravedad, float tiempo, unsigned short int anchoi,unsigned short int altoi,
            float posix, float posiy, float velox, float veloy,unsigned short int nivel);
    QTimer* animTimer;
    void moveUp2();
    void moveDown();
    void ataqueEpecial();
    void ataqueBasico();
    void consumir(unsigned short tipo);
    bool colision();
    void updateSprite();
};

#endif // JUGADOR_H
