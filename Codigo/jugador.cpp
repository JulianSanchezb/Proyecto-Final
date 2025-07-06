#include "jugador.h"
#include "jefe.h"
#include "obstaculos.h"

jugador::jugador(short int salu, float gravedad, float tiempo, unsigned short int anchoi,unsigned short int altoi, float posix, float posiy, float velox, float veloy,unsigned short int nivel) {
    setSalud(salu);
    setGravedad(gravedad);
    setTiempo(tiempo);
    setAncho(anchoi);
    setAlto(altoi);
    setGround(true);
    pos = QPointF(posix,posiy);
    posx = posix;
    posy = posiy;
    velx = velox;
    vely = veloy;
    saludables = 0;
    energia = 0;
    guilan = nullptr;

    switch(nivel){
    case 1:
        frameIndex = 0;
        animTimer = new QTimer(this);

        idleFrames.append(QPixmap(":/Multimedia/Goku1.1.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.2.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.3.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.4.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.5.png"));
        if (!idleFrames.isEmpty())
            setPixmap(idleFrames[0]);

        connect(animTimer, &QTimer::timeout, this, &jugador::updateSprite);
        animTimer->start(200);
        break;
    case 2:
        break;
    }
}

void jugador::moveUp2(){
    posy -= vely;
    setPos(posx, posy);
}

void jugador::moveDown() {
    posy += vely;
    setPos(posx, posy);
}

void jugador::ataqueEpecial(){

}

void jugador::ataqueBasico(){
    short int saludGuilan = guilan->getSalud();
    if(colision()){
        saludGuilan = saludGuilan - 3;
        guilan->setSalud(saludGuilan);
    }
}

void jugador::consumir(unsigned short int tipo){
    switch(tipo){
    case 1:
        if (saludables != 0){
            short int saludGoku = this->getSalud();
            this->setSalud(saludGoku + 20);
            saludables = saludables - 1;
        }
        break;
    }
}

bool jugador::colision(){
    if(collidesWithItem(guilan)){
        return true;
    }else{
        return false;
    }
}

void jugador::updateSprite() {
    if (idleFrames.isEmpty()) return;
    setPixmap(idleFrames[frameIndex]);
    frameIndex = (frameIndex + 1) % idleFrames.size();
}
