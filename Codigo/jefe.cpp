#include "jefe.h"
#include "jugador.h"
#include <QLineF>
#include <cmath>
using namespace std;

jefe::jefe(unsigned short int salu, int gravedad, int tiempo, unsigned short int anchoi,
           unsigned short int altoi, int posix, int posiy, int velox, int veloy,
           jugador* goku)
    //: QGraphicsPixmapItem(nullptr) // hereda de QGraphicsPixmapItem
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

    idleFrames.append(QPixmap(":/Multimedia/giran1.01.png"));
    idleFrames.append(QPixmap(":/Multimedia/giran1.02.png"));
    idleFrames.append(QPixmap(":/Multimedia/giran1.03.png"));
    idleFrames.append(QPixmap(":/Multimedia/giran1.04.png"));
    idleFrames.append(QPixmap(":/Multimedia/giran1.05.png"));
    if (!idleFrames.isEmpty()){
        setPixmap(idleFrames[0]);
    }

    connect(Timerbasic, &QTimer::timeout, this, &jefe::updateSprite);
    Timerbasic->start(200);

    connect(animTimer, &QTimer::timeout, this, [this]() {

        if(getSalud() <= 50 && !bandera){
            bandera = true;
            if (!Timersecond->isActive()) {
                connect(Timersecond, &QTimer::timeout, this, [this]() {
                    moveUp();
                    if(getGround()){
                        explosion();
                    }
                });
                Timersecond->start(4000);
            }
        }
        if(Goku->x() > x() && Goku->x() < x() + 5){
            if(!bandera){
                explosion();
            }
        }else if(Goku->x() > x()+5 && Goku->x() < x() + 15){
            ataqueBasico();
        }
    });
    animTimer->start(4000);



}

void jefe::ataqueBasico() {

    hitFrames.clear();
    hitFrames.append(QPixmap(":/Multimedia/giran2.01.png"));
    hitFrames.append(QPixmap(":/Multimedia/giran2.02.png"));
    hitFrames.append(QPixmap(":/Multimedia/giran2.03.png"));
    hitFrames.append(QPixmap(":/Multimedia/giran2.02.png"));
    hitFrames.append(QPixmap(":/Multimedia/giran2.03.png"));

    frameCount = 0;

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
                int saludgoku = Goku->getSalud() - 5;
                Goku->setSalud(saludgoku);
            }
        }
    });
    ataqueTimer->start(200);  // 200 ms por frame
}



void jefe::explosion() {
    hitFrames.clear();
    hitFrames.append(QPixmap(":/Multimedia/giran3.01.png"));
    hitFrames.append(QPixmap(":/Multimedia/giran3.02.png"));
    hitFrames.append(QPixmap(":/Multimedia/giran3.03.png"));

    frameCount = 0;

    QTimer* explosionTimer = new QTimer(this);
    connect(explosionTimer, &QTimer::timeout, this, [=]() mutable {
        if (frameCount < hitFrames.size()) {
            setPixmap(hitFrames[frameCount]);
            frameCount++;
        } else {
            explosionTimer->stop();
            explosionTimer->deleteLater();

            // Daño después de la animación
            float danioMax = 30.0;
            float epsilon = 2.0;

            QPointF miPos = this->pos();
            QPointF objetivoPos = Goku->pos();

            float distancia = QLineF(miPos, objetivoPos).length();
            int danio = danioMax / pow(distancia + epsilon, 2);

            int saludgoku = Goku->getSalud() - danio;
            Goku->setSalud(saludgoku);
        }
    });
    explosionTimer->start(200);  // 200 ms por frame
}

void jefe::moveUp() {  //Verificar el movimiento horizontal cuando está en el aire
    // Control horizontal
    velx = 0;

    // Aplicar gravedad
    vely += getGravedad();

    // Actualizar posición
    posx += velx;
    posy += vely;

    // Colisión con el suelo
    if (posy >= 560) {
        posy = 560;
        vely = 0;
        setGround(true);
    } else {
        setGround(false);;
    }

    // Actualizar posición visual
    this->setPos(posx, posy);
}

void jefe::moveRight() {
    posx += velx;
    setPos(posx, posy);
}

void jefe::moveLeft() {
    posx -= velx;
    setPos(posx, posy);
}

void jefe::updateSprite() {
    if (idleFrames.isEmpty()) return;
    setPixmap(idleFrames[frameIndex]);
    frameIndex = (frameIndex + 1) % idleFrames.size();
}



bool jefe::colision(){
    if(collidesWithItem(Goku)){
        return true;
    }else{
        return false;
    }
}


