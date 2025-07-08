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
    //pos = QPointF(posix,posiy);
    posx = posix;
    posy = posiy;
    velx = velox;
    vely = veloy;
    saludables = 0;
    energia = 0;
    guilan = nullptr;
    estado = 0;

    switch(nivel){
    case 1:
        frameIndex = 0;
        animTimer = new QTimer(this);

        idleFrames.append(QPixmap(":/Multimedia/Goku1.1.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.2.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.3.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.4.png"));
        idleFrames.append(QPixmap(":/Multimedia/Goku1.5.png"));
        if (!idleFrames.isEmpty()){
            setPixmap(idleFrames[0]);
        }

        hitFrames.append(QPixmap(":/Multimedia/Goku1/Gokul1.png"));
        hitFrames.append(QPixmap(":/Multimedia/Goku1/Gokul2.png"));

        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul1.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul2.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul3.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul4.png"));

        connect(animTimer, &QTimer::timeout, this, [=]() {
            if(getSalud() <= 0){
                estado = 2;
            }
            actualizarSprite();
        });
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

void jugador::actualizarSprite() {
    switch (estado) {
    case 0: // Normal
        setPixmap(idleFrames[frameIndex % idleFrames.size()]);
        if(frameIndex >=idleFrames.size()){
            frameIndex = 0;
        }
        break;
    case 1: // Daño
        setPixmap(hitFrames[frameIndex % hitFrames.size()]);
        if(frameIndex >= hitFrames.size()){
            frameIndex = 0;
            estado = 0;
        }
        break;
    case 2: // Muerte
        if(frameIndex < spritesMuerte.size()){
            setPixmap(spritesMuerte[frameIndex % spritesMuerte.size()]);
        }
        if(frameIndex >= spritesMuerte.size()){
            animTimer->stop();
        }
        break;
    }
    frameIndex++;
}

void jugador::recibirDano(){
    if(hitFrames.isEmpty()) return;
    setPixmap(hitFrames[frameIndex]);
    frameIndex = (frameIndex + 1) % hitFrames.size();
}




//Setters
void jugador::setEnergia(short int e){
    energia = e;
}

void jugador::setSaludables(short int s){
    saludables = s;
}

void jugador::setEstado(short int e){
    estado = e;
}

void jugador::resetAnimtimer(){
    animTimer->start(200);
}
