#include "jefe.h"
#include "jugador.h"
#include <QLineF>
#include <cmath>
using namespace std;

jefe::jefe(unsigned short int salu, int gravedad, int tiempo, unsigned short int anchoi,
           unsigned short int altoi, int posix, int posiy, int velox, int veloy,
           jugador* goku)
{
    // Atributos básicos
    setSalud(salu);
    setGravedad(gravedad);
    setTiempo(tiempo);
    setAncho(anchoi);
    setAlto(altoi);
    setGround(true);

    posx = posix;
    posy = posiy;
    velx = velox;
    vely = veloy;
    Goku = goku;

    frameIndex = 0;

    animTimer = new QTimer(this);
    Timersecond = new QTimer(this);
    Timerbasic = new QTimer(this);

    idleFrames.clear();
    idleFrames.append(QPixmap(":/Multimedia/giran5.01.png").scaled(135,135));
    idleFrames.append(QPixmap(":/Multimedia/giran5.02.png").scaled(135,135));
    idleFrames.append(QPixmap(":/Multimedia/giran5.03.png").scaled(135,135));
    idleFrames.append(QPixmap(":/Multimedia/giran5.04.png").scaled(135,135));
    idleFrames.append(QPixmap(":/Multimedia/giran5.05.png").scaled(135,135));

    for (int i = 1; i <= 5; ++i) {
        rightFrames.append(QPixmap(QString(":/Multimedia/giran1.0%1.png").arg(i)));
        leftFrames.append(QPixmap(QString(":/Multimedia/giran1.1%1.png").arg(i)));
    }
    currentFrames = &rightFrames;

    connect(animTimer, &QTimer::timeout, this, [this]() {
        if (getSalud() <= 0 && !muerto) {
            muerto = true;
            animTimer->stop();

            currentFrames = &idleFrames;
            frameIndex = 0;

            QTimer* muerteTimer = new QTimer(this);
            connect(muerteTimer, &QTimer::timeout, this, [=]() mutable {
                if (frameIndex < currentFrames->size()) {
                    setPixmap((*currentFrames)[frameIndex]);
                    frameIndex++;
                } else {
                    muerteTimer->stop();
                    muerteTimer->deleteLater();
                    deleteLater();
                }
            });

            muerteTimer->start(300);
            return; //evita que el animTimer siga ejecutando lógica normal
        }


        if(getGround()){
            if(x() >= 390 && x() <= 430){
                ataqueBasico(0);
                banderapos = false;
            }else if(x() >= 1 && x() <= 4){
                ataqueBasico(1);
                banderapos = true;
            }

            if(banderapos){
                if(colision()){
                    moveLeft();
                }
                moveRight();
            }else if(!banderapos){
                if(colision()){
                    moveRight();
                }
                moveLeft();

            }
            updateSprite();
        }


        if(getSalud() <= 350 && !bandera){
            bandera = true;
            if (!Timersecond->isActive()) {
                connect(Timersecond, &QTimer::timeout, this, [this]() {
                    moveUp();
                });
                Timersecond->start(10000);
            }
        }


        if(colision()){
            contador++;
            if(banderapos){
                ataqueBasico(1);
            }else if(!banderapos){
                ataqueBasico(0);
            }
        }
        if(!bandera){
            if(contador == 5){
                contador = 0;
                explosion();
            }
        }

    });
    animTimer->start(300);
}



void jefe::ataqueBasico(bool posicion) {
    if (animTimer->isActive()) {
        animTimer->stop();
    }
    if(posicion){
        hitFrames.clear();
        hitFrames.append(QPixmap(":/Multimedia/giran2.01.png"));
        hitFrames.append(QPixmap(":/Multimedia/giran2.02.png"));
        hitFrames.append(QPixmap(":/Multimedia/giran2.03.png"));
        hitFrames.append(QPixmap(":/Multimedia/giran2.02.png"));
        hitFrames.append(QPixmap(":/Multimedia/giran2.03.png"));

        frameCount = 0;
    }else{
        hitFrames.clear();
        hitFrames.append(QPixmap(":/Multimedia/giran2.11.png"));
        hitFrames.append(QPixmap(":/Multimedia/giran2.12.png"));
        hitFrames.append(QPixmap(":/Multimedia/giran2.13.png"));
        hitFrames.append(QPixmap(":/Multimedia/giran2.12.png"));
        hitFrames.append(QPixmap(":/Multimedia/giran2.13.png"));

        frameCount = 0;
    }
    QTimer* ataqueTimer = new QTimer(this);
    connect(ataqueTimer, &QTimer::timeout, this, [=]() mutable {
        if (frameCount < hitFrames.size()) {
            setPixmap(hitFrames[frameCount]);
            frameCount++;
        } else {

            ataqueTimer->stop();
            ataqueTimer->deleteLater();

            // Daño si colisiona (una sola vez, después de la animación)
            if (colision()) {
                int saludgoku = Goku->getSalud() - 10;
                Goku->setSalud(saludgoku);
                if(Goku->getSalud() > 0){
                    Goku->setEstado(1);
                    frameIndex = 0;
                    //Goku->actualizarSprite();
                }
            }
            if (!animTimer->isActive()) {
                animTimer->start();  // o solo start() si ya configuraste el intervalo
            }
        }
    });
    ataqueTimer->start(200);  // 200 ms por frame
}


void jefe::explosion() {
    if (animTimer->isActive()) {
        animTimer->stop();
    }
    hitFrames.clear();
    hitFrames.append(QPixmap(":/Multimedia/giran3.01.png").scaled(135,135));
    hitFrames.append(QPixmap(":/Multimedia/giran3.02.png").scaled(135,135));
    hitFrames.append(QPixmap(":/Multimedia/giran3.03.png").scaled(135,135));
    hitFrames.append(QPixmap(":/Multimedia/giran3.04.png").scaled(135,135));
    hitFrames.append(QPixmap(":/Multimedia/giran3.05.png").scaled(135,135));
    hitFrames.append(QPixmap(":/Multimedia/giran3.06.png").scaled(135,135));

    frameCount = 0;

    QTimer* explosionTimer = new QTimer(this);
    connect(explosionTimer, &QTimer::timeout, this, [=]() mutable {
        if (frameCount < hitFrames.size()) {
            setPixmap(hitFrames[frameCount]);
            frameCount++;
            // Daño después de la animación
            float danioMax = 700.0;
            float epsilon = 1.0;

            float distancia = std::abs(x() - Goku->x());
            int danio = danioMax / pow( distancia/15 + epsilon, 2);// division por 15 es un medida de conversion practica


            if(danio > 5 && Goku->getSalud() > 0){
                int saludgoku = Goku->getSalud() - danio;

                Goku->setSalud(saludgoku);
                Goku->setEstado(1);
                frameIndex = 0;
                //Goku->actualizarSprite();
            }

        } else {

            explosionTimer->stop();
            explosionTimer->deleteLater();

            if (!animTimer->isActive()) {
                animTimer->start();  // o solo start() si ya configuraste el intervalo
            }
        }

    });
    explosionTimer->start(200);  // 200 ms por frame

}

void jefe::moveUp() {
    int direccion;
    if (animTimer->isActive()) {
        animTimer->stop();
    }
    if(banderapos){
        hitFrames.clear();
        hitFrames.append(QPixmap(":/Multimedia/giran4.01.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.02.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.03.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.04.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.05.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.06.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.07.png").scaled(135, 135));
        direccion = 1;
    }else if(!banderapos){
        hitFrames.clear();
        hitFrames.append(QPixmap(":/Multimedia/giran4.11.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.12.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.13.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.14.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.15.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.16.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.17.png").scaled(135, 135));
        direccion  = -1;
    }

    frameCount = 0;
    vely = -15;

    QTimer* saltoTimer = new QTimer(this);
    connect(saltoTimer, &QTimer::timeout, this, [=]() mutable {
        // Animación de salto
        if (frameCount < hitFrames.size()) {
            setPixmap(hitFrames[frameCount]);
            frameCount++;
        }

        // Movimiento vertical con gravedad
        vely += getGravedad();
        posy += vely;

        // Movimiento horizontal
        posx += (direccion)*5;
        if(x() >= 450){
            posx = 440;
        }else if(x() <= 1){
            posx = 3;
        }

        // Colisión con el suelo
        if (posy >= 190) {
            posy = 190;
            vely = 0;
            setGround(true);
            setPos(posx, posy);
            explosion();  // o lo que se quiera que ocurra al aterrizar
            if (!animTimer->isActive()) {
                animTimer->start();  // o solo start() si ya configuraste el intervalo
            }
            saltoTimer->stop();
            saltoTimer->deleteLater();
            return;
        } else {
            setGround(false);
        }

        setPos(posx, posy);
    });

    saltoTimer->start(50);  // más frecuente para suavizar
}


void jefe::moveRight() {
    currentFrames = &rightFrames;
    posx += velx;
    setPos(posx, posy);
}

void jefe::moveLeft() {
    currentFrames = &leftFrames;
    posx -= velx;
    setPos(posx, posy);
}

void jefe::updateSprite() {
    if (!currentFrames || currentFrames->isEmpty()) return;
    setPixmap((*currentFrames)[frameIndex]);
    frameIndex = (frameIndex + 1) % currentFrames->size();
}

bool jefe::colision(){
    if(collidesWithItem(Goku)){
        if(Goku->getSalud() > 0){
            Goku->setEstado(1);
            frameIndex = 0;
        }
        return true;
    }else{
        return false;
    }
}


