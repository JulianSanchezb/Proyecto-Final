#include "obstaculos.h"
#include "jugador.h"
#include "jefe.h"

using namespace std;

obstaculos::obstaculos(float x, float y, float velox, float veloy, float tiempo, float gravedad, int anchoi,
                       int altoi, jugador* Gokui, unsigned short int tipo)
    : QGraphicsPixmapItem(nullptr)
{
    posx = x;
    posy = y;
    velx = velox;
    vely = veloy;
    t = tiempo;
    g = gravedad;
    ancho = anchoi;
    alto = altoi;
    Goku = Gokui;
    Guiran = nullptr;
    disponible = false;
    limiteinferior = 100;
    limitesuperior = -100;
    limiteizquierda = -1000;
    limitederecha = 1000;

    timer = new QTimer(this);
    QPixmap img;

    switch(tipo){
    case 1: // cámara
        idleFrames.append(QPixmap(":/Multimedia/camara.01.png").scaled(20, 20));
        idleFrames.append(QPixmap(":/Multimedia/camara.02.png").scaled(20, 20));
        idleFrames.append(QPixmap(":/Multimedia/camara.03.png").scaled(20, 20));

        // Animación de disparo
        shootFrames.append(QPixmap(":/Multimedia/camaraD1.png").scaled(27, 27));
        shootFrames.append(QPixmap(":/Multimedia/CamaraD2.png").scaled(27, 27));

        frames = idleFrames;
        frameCount = frames.size();
        frameIndex = 0;

        setPixmap(frames[0]);

        connect(timer, &QTimer::timeout, this, &obstaculos::moveeny);
        timer->start(250);
        break;
    case 2: // pájaros
        frames.append(QPixmap(":/Multimedia/pajaro.01.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/pajaro.02.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/pajaro.03.png").scaled(10, 10));

        frameCount = frames.size();
        frameIndex = 0;

        setPixmap(frames[0]);

        connect(timer, &QTimer::timeout, this, &obstaculos::moveSenoidal);
        break;
    case 3: // proyectiles que giran
        frames.append(QPixmap(":/Multimedia/proyectil.1.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/proyectil.2.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/proyectil.3.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/proyectil.4.png").scaled(10, 10));

        frameCount = frames.size();
        frameIndex = 0;

        setPixmap(frames[0]);

        connect(timer, &QTimer::timeout, this, &obstaculos::moveParabolico);
        break;
    case 4: // balas
        frames.append(QPixmap(":/Multimedia/bala1.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/bala2.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/bala3.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/bala4.png").scaled(10, 10));

        frameCount = frames.size();
        frameIndex = 0;

        setPixmap(frames[0]);

        connect(timer, &QTimer::timeout, this, &obstaculos::moveRecto);
        break;
    case 5:
        frames.append(QPixmap(":/Multimedia/esfera4.png").scaled(15, 15));

        frameCount = frames.size();
        frameIndex = 0;

        setPixmap(frames[0]);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveEsfera);
        break;
    }
    setPixmap(img);
}

obstaculos::~obstaculos() {
    if (timer) {
        timer->stop();
    }

    frames.clear();
    idleFrames.clear();
    shootFrames.clear();
}

void obstaculos::moveeny(){
    int limitesuperior = 0;
    int limiteinferior = 103;
    if (y() < limitesuperior || y() > limiteinferior){
        vely = vely * (-1);
    }
    setY(y() + vely);

    if (!frames.isEmpty()) {
        frameIndex = (frameIndex + 1) % frameCount;
        setPixmap(frames[frameIndex]);
    }

    if (disparando && frameIndex == frameCount - 1) {
        disparando = false;
        frames = idleFrames;
        frameCount = frames.size();
        frameIndex = 0;
    }

    if(colision()){
        short int salud = Goku->getSalud() - 10;
        Goku->setSalud(salud);
    }

}

void obstaculos::moveSenoidal() {
    if (!disponible) return;
    int amplitud = 25;
    float frecuencia= 2;
    int limite = 300;
    int velX = 5;
    float y = amplitud * sin(t * frecuencia) + y0;
    t+=0.1;
    setPos(x() + velX, y);
    frameIndex = (frameIndex + 1) % frameCount;
    setPixmap(frames[frameIndex]);

    if(x()> limite || colision()){
        if(colision()){
        short int salud = Goku->getSalud() - 10;
        Goku->setSalud(salud);
        }
        desactivar();
    }
}

void obstaculos::moveParabolico() {
    if (!disponible) return;

    t += 0.5; // incremento de tiempo

    // Movimiento parabólico
    double vx = (direccion)*20;
    double vy = -10;

    double xr = x0 + vx * t;
    double yr = y0 + vy * t - 0.5 * g * t * t ;

    setPos(xr,yr);

    frameIndex = (frameIndex + 1) % frameCount;
    setPixmap(frames[frameIndex]);

    if(y()> 250 || x() >450 || colision()){
        if(colision()){
            short int salud = Goku->getSalud() - 10;
            Goku->setSalud(salud);
        }
        desactivar();
    }
}


void obstaculos::moveRecto() {
    int limite = 300;
    if (!disponible) return;

    int velocidad = 15;
    setPos(x() + velocidad, y());

    frameIndex = (frameIndex + 1) % frameCount;
    setPixmap(frames[frameIndex]);


    if (x() > limite || colision()) {
        if(colision()){
            short int salud = Goku->getSalud() - 10;
            Goku->setSalud(salud);
        }
        desactivar();
    }
}

void obstaculos::animarDisparo() {
    if (!shootFrames.isEmpty()) {
        frames = shootFrames;
        frameCount = frames.size();
        frameIndex = 0;
        disparando = true;
    }
}

void obstaculos::activar(QPointF posicion,int tiempo) {
    setPos(posicion);

    x0 = posicion.x();
    y0 = posicion.y();
    t = 0;
    disponible = true;
    setVisible(true);

    if(!timer->isActive()){
        timer->start(tiempo);
    }
}

void obstaculos::desactivar() {
    disponible = false;
    setVisible(false);

    if (timer->isActive()) {
        timer->stop();
    }

}

bool obstaculos::colision(){
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

void obstaculos::moveEsfera() {
    if (!disponible) return;

    int velocidad = 20 * direccion;
    if(direccion == 0){
        velocidad = 20;
    }

    setPos(x() + velocidad, y());

    frameIndex = (frameIndex + 1) % frameCount;
    setPixmap(frames[frameIndex]);
    if(Guiran){
        if (x() > 500 || x() < 1 ||collidesWithItem(Guiran)){
            if(collidesWithItem(Guiran)){
                short int salud = Guiran->getSalud() - 40;
                Guiran->setSalud(salud);
            }
            desactivar();
        }
    }

}

bool obstaculos::getdisponible(){
    return disponible;
}

bool obstaculos::setDisponible(bool tipo){
    return (disponible = tipo);
}

void obstaculos::setGuiran(jefe* g){
    Guiran = g;
}
