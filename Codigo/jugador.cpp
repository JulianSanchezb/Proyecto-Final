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
    if (movTimer) {
        movTimer->stop();
    }
    if (animTimer) {
        animTimer->stop();
    }
    if(banderapos){
        moveFrames.clear();
        moveFrames.append(QPixmap(":/Multimedia/goku4.01.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.02.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.03.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.04.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.05.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.06.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.07.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.08.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.09.png").scaled(90, 90));
        direccion = 1;
    } else {
        moveFrames.clear();
        moveFrames.append(QPixmap(":/Multimedia/goku4.11.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.12.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.13.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.14.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.15.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.16.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.17.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.18.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku4.19.png").scaled(90, 90));
        direccion = -1;
    }

    frameCount = 0;
    vely = -15;

    QTimer* saltoTimer = new QTimer(this);
    connect(saltoTimer, &QTimer::timeout, this, [=]() mutable {
        if (frameCount < moveFrames.size()) {
            setPixmap(moveFrames[frameCount]);
            frameCount++;
        }
        vely += getGravedad();
        posy += vely;
        posx += direccion * 10;

        if(colision(3)){
            posx = 450;
        }else if(colision(2)){
            posx = 4;
        }

        if (posy >= 190) {
            posy = 190;
            vely = 0;
            setGround(true);
            animTimer->start();
            movTimer->start();
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
    saltoTimer->start(100);
}

void jugador::moveRight() {
    velx = 10;
    animTimer->stop();
    if (direccionMovimiento == 1) return;

    banderapos = true;
    direccionMovimiento = 1;

    if (movTimer) {
        movTimer->stop();
        movTimer->deleteLater();
    }
    movTimer = new QTimer(this);
    moveFrames.clear();
    moveFrames.append(QPixmap(":/Multimedia/goku2.01.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.02.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.03.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.04.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.05.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.06.png").scaled(90, 90));
    frameCount = 0;

    connect(movTimer, &QTimer::timeout, this, [=]() mutable {
        if (frameCount < moveFrames.size()) {
            setPixmap(moveFrames[frameCount]);
            frameCount++;
        } else {
            frameCount = 0;
        }
        if (!colision(3)) {
            posx += velx;
            setPos(posx, posy);
        } else {
            detenerMovimiento();
        }
    });

    movTimer->start(100);
}

void jugador::moveLeft() {
    velx = 10;
    animTimer->stop();
    if (direccionMovimiento == -1) return;

    banderapos = false;
    direccionMovimiento = -1;

    if (movTimer) {
        movTimer->stop();
        movTimer->deleteLater();
    }
    movTimer = new QTimer(this);

    moveFrames.clear();
    moveFrames.append(QPixmap(":/Multimedia/goku2.11.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.12.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.13.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.14.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.15.png").scaled(90, 90));
    moveFrames.append(QPixmap(":/Multimedia/goku2.16.png").scaled(90, 90));
    frameCount = 0;

    connect(movTimer, &QTimer::timeout, this, [=]() mutable {
        if (frameCount < moveFrames.size()) {
           setPixmap(moveFrames[frameCount]);
            frameCount++;
        } else {
            frameCount = 0;
        }
        if (!colision(2)) {
            posx -= velx;
            setPos(posx, posy);
        } else {
            detenerMovimiento();
        }
    });

    movTimer->start(100);
}

void jugador::ataqueEspecial() {
    ataqueBasico();
    especial = true;
    QTimer::singleShot(1000, this, [=]() {
        especial = false;
    });
    energia --;
}

void jugador::ataqueBasico() {
    if (atacando) return;  // Evita múltiples ataques simultáneos
    atacando = true;

    if (animTimer) animTimer->stop();
    if (movTimer) {
        movTimer->stop();
        movTimer->deleteLater();
        movTimer = nullptr;
    }

    estado = 1;
    frameCount = 0;
    moveFrames.clear();

    if (banderapos) {
        moveFrames.append(QPixmap(":/Multimedia/goku5.01.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku5.02.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku5.03.png").scaled(90, 90));
    } else {
        moveFrames.append(QPixmap(":/Multimedia/goku5.11.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku5.12.png").scaled(90, 90));
        moveFrames.append(QPixmap(":/Multimedia/goku5.13.png").scaled(90, 90));
    }

    QTimer* ataqueTimer = new QTimer(this);
    connect(ataqueTimer, &QTimer::timeout, this, [=]() mutable {
        if (frameCount < moveFrames.size()) {
            setPixmap(moveFrames[frameCount]);
            frameCount++;

            // Colisión con enemigo durante el ataque
            if (colision(1)) {
                short int saludGuilan = guilan->getSalud() - 10;
                guilan->setSalud(saludGuilan);
            }
        } else {
            ataqueTimer->stop();
            ataqueTimer->deleteLater();
            atacando = false;
            estado = 0;
            if (animTimer) animTimer->start();
        }
    });

    ataqueTimer->start(100);
}


void jugador::consumir(unsigned short int tipo) {
    if (tipo == 1 && saludables != 0) {
        setSalud(getSalud() + 32);
        if(saludables > 0){
            saludables--;
        }
    }
}

bool jugador::colision(int caso) {
    switch (caso) {
    case 1:
        return collidesWithItem(guilan);
    case 2:
        return posx <= 4;
    case 3:
        return posx >= 450;
    default:
        return false;
    }
}

void jugador::actualizarSprite() {
    //if (direccionMovimiento != 0 || !getGround()) return;
    //qDebug()<<estado;
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
    case 3: // MOVIMIENTO
        if (!moveFrames.isEmpty())
            setPixmap(moveFrames[frameIndex % moveFrames.size()]);
        break;
    }
    frameIndex++;
}

void jugador::detenerMovimiento() {
    direccionMovimiento = 0;
    estado = 0;
    if (movTimer && movTimer->isActive()) {
        movTimer->stop();
        animTimer->start();
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


        hitFrames.append(QPixmap(":/Multimedia/Goku1/Gokul1.png"));
        hitFrames.append(QPixmap(":/Multimedia/Goku1/Gokul2.png"));

        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul1.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul2.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul3.png"));
        spritesMuerte.append(QPixmap(":/Multimedia/Goku1/Gokul4.png"));
        break;
    case 2:
        idleFrames.append(QPixmap(":/Multimedia/goku3.01.png").scaled(90,90));
        idleFrames.append(QPixmap(":/Multimedia/goku3.02.png").scaled(90,90));
        idleFrames.append(QPixmap(":/Multimedia/goku3.03.png").scaled(90,90));
        idleFrames.append(QPixmap(":/Multimedia/goku3.04.png").scaled(90,90));
        idleFrames.append(QPixmap(":/Multimedia/goku3.05.png").scaled(90,90));

        hitFrames.append(QPixmap(":/Multimedia/goku6.01.png").scaled(90,90));
        hitFrames.append(QPixmap(":/Multimedia/goku6.02.png").scaled(90,90));
        hitFrames.append(QPixmap(":/Multimedia/goku6.03.png").scaled(90,90));
        hitFrames.append(QPixmap(":/Multimedia/goku6.04.png").scaled(90,90));

        spritesMuerte.append(QPixmap(":/Multimedia/goku7.png").scaled(90,90));

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
        });
        animTimer->start(100);
    }

}

void jugador::actualizarMovimiento() {
    if (keysPressed.contains(Qt::Key_A) && !keysPressed.contains(Qt::Key_D)) {
        if(!colision(2) && getSalud() > 0){
         moveLeft();
        }
    } else if (keysPressed.contains(Qt::Key_D) && !keysPressed.contains(Qt::Key_A)) {
        if(!colision(3) && getSalud() > 0){
         moveRight();
        }
    }else if(keysPressed.contains(Qt::Key_E)&& !keysPressed.contains(Qt::Key_D) && !keysPressed.contains(Qt::Key_A)){
        if( getSalud() > 0){
         ataqueBasico();
        }
    } else {
        detenerMovimiento();
    }
}

//Getters
short int jugador::getSaludables(){return saludables;}
short int jugador::getEnergia(){return energia;}
int jugador::getdireccion(){
    return direccionMovimiento;
}

//Setters
void jugador::setEnergia(short int e) { energia = e; }
void jugador::setSaludables(short int s) { saludables = s; }
void jugador::setEstado(short int e) { estado = e; }
void jugador::setGuilan(jefe* G){guilan = G;}
void jugador::resetAnimtimer() {
    if (animTimer) animTimer->start(200);
}



