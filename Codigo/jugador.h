#ifndef JUGADOR_H
#define JUGADOR_H
#include "personaje.h"
#include <QTimer>
#include <QSet>

class jefe;

class jugador : public personaje
{
private:
    jefe *guilan;
    short int energia;
    short int saludables;
    short int estado;
    QVector<QPixmap> spritesMuerte;
    QVector<QPixmap> moveFrames;
    bool banderapos;
    unsigned short int nivel = 1;
    short int direccionMovimiento = 0;
    bool atacando = false;

public:
    jugador(short int salu, float gravedad, float tiempo, unsigned short int anchoi,unsigned short int altoi,
            float posix, float posiy, float velox, float veloy);
    QTimer* animTimer = nullptr;
    QTimer* movTimer = nullptr;
    QSet<int> keysPressed;

    void moveUp1();
    void moveRight1();
    void moveLeft1();
    void moveDown();
    void moveUp();
    void moveRight();
    void moveLeft();
    void ataqueEpecial();
    void ataqueBasico();
    void consumir(unsigned short tipo);
    bool colision(int caso);
    void actualizarSprite();
    void recibirDano();
    void detenerMovimiento();
    void actualizarMovimiento();
    bool derecha= false;
    bool izquierda = false;
    bool especial = false;

    int getdireccion();

    //Getters
    short int getSaludables();
    short int getEnergia();

    //Setters
    void setEnergia(short int e);
    void setSaludables(short int s);
    void setEstado(short e);
    void resetAnimtimer();
    void setnivel(unsigned short int nive);
};

#endif // JUGADOR_H
