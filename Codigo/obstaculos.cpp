#include "obstaculos.h"
#include "jugador.h"

using namespace std;
//verificar todas las medidas de la pantalla
obstaculos::obstaculos(float x, float y, float velox, float veloy, float tiempo, float gravedad, int anchoi,
                       int altoi, jugador* Gokui, unsigned short int tipo)
    : QGraphicsPixmapItem(nullptr) // importante: inicializa como QGraphicsPixmapItem
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
    disponible = false;
    limiteinferior = 100;
    limitesuperior = -100;
    limiteizquierda = -1000;
    limitederecha = 1000;

    // Cargar sprite según el tipo
    QPixmap img;

    switch(tipo){
    case 1: // cámara
        img.load(":/Multimedia/camara.01.png");
        img = img.scaled(20, 20);
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveeny);
        timer->start(30);
        break;
    case 2: // pájaros
        frames.append(QPixmap(":/Multimedia/pajaro.01.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/pajaro.02.png").scaled(10, 10));
        frames.append(QPixmap(":/Multimedia/pajaro.03.png").scaled(10, 10));

        frameCount = frames.size();
        frameIndex = 0;

        setPixmap(frames[0]);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveSenoidal);
        break;
    case 3: // proyectiles que giran
        img.load(":/sprites/proyectil.png");
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveParabolico);
        break;
    case 4: // balas
        img.load(":/Multimedia/bala.png");
        img = img.scaled(5, 5);
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveRecto);
        break;
    }

    setPixmap(img);
    //setPos(posx, posy);  // coloca el sprite en pantalla
}

void obstaculos::moveeny(){
    int limitesuperior = 0;
    int limiteinferior = 103;
    if (y() == limitesuperior || y() == limiteinferior){
        vely = vely * (-1);
    }
    setY(y() + vely);
}

void obstaculos::moveSenoidal() {
    if (!disponible) return;
    int amplitud = 25;
    float frecuencia= 2;
    int limite = 300;
    int velX = 5;
    float y = amplitud * sin(t * frecuencia) + y0;
    t+=0.1;
    setPos(x() + velX, y); // Qt: actualiza posición del objeto en escena
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

    t += 0.1; // incremento de tiempo
    double v0 = 5;
    double rad = qDegreesToRadians(45.0);
    // Movimiento parabólico
    double vx = v0 * qCos(rad);
    double vy = v0 * qSin(rad);

    double x = posx + vx * t;
    double y = posy + vy * t - 0.5 * g * t * t;

    setPos(x,y);

    if (x > limiteizquierda ||x>= limiteinferior || colision()) {//modificar para que se detenga cuando hay colison o salga de la escena
        desactivar();
        return;
    }
}

void obstaculos::moveRecto() {
    int limite = 300;
    if (!disponible) return;

    int velocidad = 15;
    setPos(x() + velocidad, y());

    if (x() > limite || colision()) {
        desactivar();
    }
}

void obstaculos::activar(QPointF posicion,int tiempo) {
    setPos(posicion);
    y0 = posicion.y();
    t = 0;
    disponible = true;
    setVisible(true);
    if (timer) timer->start(tiempo);
}

void obstaculos::desactivar() {
    disponible = false;
    setVisible(false);
    if (timer) timer->stop();
}

bool obstaculos::colision(){
    if(collidesWithItem(Goku)){
        return true;
    }else{
        return false;
    }
}

QRectF obstaculos::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

bool obstaculos::getdisponible(){
    return disponible;
}

bool obstaculos::setDisponible(bool tipo){
    return (disponible = tipo);
}
