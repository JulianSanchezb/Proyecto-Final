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
    QVector<QPixmap> rightFrames;
    QVector<QPixmap> leftFrames;
    QVector<QPixmap>* currentFrames = nullptr;
    bool bandera = false;
    bool banderapos = true;
    bool muerto = false;
    unsigned short int contador = 0;
    void moveUp()override;
    void moveRight()override;
    void moveLeft()override;
public:
    jefe(unsigned short salu, int gravedad, int tiempo, unsigned short ancho, unsigned short alto,
         int posix, int posiy, int velox, int veloy, jugador *goku);
    void ataqueBasico(bool posicion);
    void explosion();
    bool colision();
    void updateSprite();
};

#endif // JEFE_H
