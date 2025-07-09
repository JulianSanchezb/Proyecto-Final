#include "jugador.h"
#include "jefe.h"
#include "obstaculos.h"

jugador::jugador(short int salu, float gravedad, float tiempo, unsigned short int anchoi,unsigned short int altoi, float posix, float posiy, float velox, float veloy) {
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
    saludables = 0;
    energia = 0;
    guilan = nullptr;
    estado = 0;
    direccionMovimiento = 0;
    animTimer = nullptr;
    frameCount = 0;
    frameIndex = 0;
    banderapos = true;
    qDebug() << nivel;
}

void jugador::moveUp1(){
    posy -= vely;
    setPos(posx, posy);
}

void jugador::moveRight1(){
    posx += velx;
    setPos(posx, posy);
}

void jugador::moveLeft1(){
    posx -= velx;
    setPos(posx, posy);
}


void jugador::moveDown() {
    posy += vely;
    setPos(posx, posy);
}

void jugador::moveUp() {
    int direccion;
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
    } else {
        hitFrames.clear();
        hitFrames.append(QPixmap(":/Multimedia/giran4.11.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.12.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.13.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.14.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.15.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.16.png").scaled(135, 135));
        hitFrames.append(QPixmap(":/Multimedia/giran4.17.png").scaled(135, 135));
        direccion = -1;
    }

    frameCount = 0;
    vely = -10;

    QTimer* saltoTimer = new QTimer(this);
    connect(saltoTimer, &QTimer::timeout, this, [=]() mutable {
        if (frameCount < hitFrames.size()) {
            setPixmap(hitFrames[frameCount]);
            frameCount++;
        }
        vely += getGravedad();
        posy += vely;
        posx += direccion * 3;

        if (posy >= 190) {
            posy = 190;
            vely = 0;
            setGround(true);
            setPos(posx, posy);
            estado = 0;
            saltoTimer->stop();
            saltoTimer->deleteLater();
            return;
        } else {
            setGround(false);
        }

        setPos(posx, posy);
    });
    saltoTimer->start(50);
}

void jugador::moveRight() {
    banderapos = true;
    direccionMovimiento = 1;
    moveFrames.clear();
    moveFrames.append(QPixmap(":/Multimedia/giran1.01.png").scaled(135, 135));
    moveFrames.append(QPixmap(":/Multimedia/giran1.02.png").scaled(135, 135));
    moveFrames.append(QPixmap(":/Multimedia/giran1.03.png").scaled(135, 135));
    moveFrames.append(QPixmap(":/Multimedia/giran1.04.png").scaled(135, 135));
    moveFrames.append(QPixmap(":/Multimedia/giran1.05.png").scaled(135, 135));
    frameCount = 0;
}

void jugador::moveLeft() {
    banderapos = false;
    direccionMovimiento = -1;
    moveFrames.clear();
    moveFrames.append(QPixmap(":/Multimedia/giran1.11.png").scaled(135, 135));
    moveFrames.append(QPixmap(":/Multimedia/giran1.12.png").scaled(135, 135));
    moveFrames.append(QPixmap(":/Multimedia/giran1.13.png").scaled(135, 135));
    moveFrames.append(QPixmap(":/Multimedia/giran1.14.png").scaled(135, 135));
    moveFrames.append(QPixmap(":/Multimedia/giran1.15.png").scaled(135, 135));
    frameCount = 0;;
}


void jugador::ataqueEpecial() {}

void jugador::ataqueBasico() {
    if (colision()) {
        short int saludGuilan = guilan->getSalud() - 3;
        guilan->setSalud(saludGuilan);
    }
}

void jugador::consumir(unsigned short int tipo) {
    if (tipo == 1 && saludables != 0) {
        setSalud(getSalud() + 20);
        saludables--;
    }
}

bool jugador::colision() {
    return collidesWithItem(guilan);
}

void jugador::actualizarSprite() {
    switch (estado) {
    case 0:
        setPixmap(idleFrames[frameIndex % idleFrames.size()]);
        break;
    case 1:
        setPixmap(hitFrames[frameIndex % hitFrames.size()]);
        if (frameIndex >= hitFrames.size()) {
            frameIndex = 0;
            estado = 0;
        }
        break;
    case 2:
        if (frameIndex < spritesMuerte.size()) {
            setPixmap(spritesMuerte[frameIndex]);
        } else {
            animTimer->stop();
        }
        break;
    }
    frameIndex++;
}

void jugador::recibirDano() {
    if (!hitFrames.isEmpty()) {
        setPixmap(hitFrames[frameIndex]);
        frameIndex = (frameIndex + 1) % hitFrames.size();
    }
}

//Getters
short int jugador::getSaludables(){return saludables;}
short int jugador::getEnergia(){return energia;}

//Setters
void jugador::setEnergia(short int e) { energia = e; }
void jugador::setSaludables(short int s) { saludables = s; }
void jugador::setEstado(short int e) { estado = e; }

void jugador::resetAnimtimer() {
    if (animTimer) animTimer->start(200);
}

void jugador::detenerMovimiento() {
    direccionMovimiento = 0;
    if (animTimer && animTimer->isActive()) {
        setPixmap(idleFrames[0]);
    }
}

void jugador::setnivel(unsigned short int nive) {
    nivel = nive;
    frameIndex = 0;

    idleFrames.clear();
    hitFrames.clear();
    spritesMuerte.clear();

    posx = x();
    posy = y();

    switch (nivel) {
    case 1:
        idleFrames.append(QPixmap(":/Multimedia/Goku1.1.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.2.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.3.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.4.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.5.png"));
        if (!idleFrames.isEmpty()) setPixmap(idleFrames[0]);

        hitFrames.append(QPixmap(":/Multimedia/Goku1/Gokul1.png"));
        hitFrames.append(QPixmap(":/Multimedia/Goku1/Gokul2.png"));

        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul1.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul2.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul3.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul4.png"));
        break;
    case 2:
        idleFrames.append(QPixmap(":/Multimedia/Goku1.1.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.2.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.3.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.4.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.5.png"));
        if (!idleFrames.isEmpty()) setPixmap(idleFrames[0]);

        hitFrames.append(QPixmap(":/Multimedia/Goku1/Gokul1.png"));
        hitFrames.append(QPixmap(":/Multimedia/Goku1/Gokul2.png"));

        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul1.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul2.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul3.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul4.png"));
        break;
    }

    if (!animTimer) {
        animTimer = new QTimer(this);
        connect(animTimer, &QTimer::timeout, this, [=]() {
            if (getSalud() <= 0 && estado != 2){
                frameIndex = 0;
                estado = 2;
            }
            actualizarSprite();
            if (direccionMovimiento != 0) {
                posx += direccionMovimiento * velx;
                setPos(posx, posy);

                if (!moveFrames.isEmpty()) {
                    setPixmap(moveFrames[frameCount % moveFrames.size()]);
                    frameCount++;
                }
            }
        });
        animTimer->start(100);
    }

}
