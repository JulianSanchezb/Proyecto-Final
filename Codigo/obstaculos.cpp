#include "obstaculos.h"
#include "jugador.h"

using namespace std;
//verificar todas las medidas de la pantalla
obstaculos::obstaculos(float x, float y, float velox, float veloy, float tiempo, float gravedad, int anchoi,
                       int altoi, jugador* Gokui, unsigned short int tipo) {
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
    switch(tipo){
    case 1: // para la camara
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveeny);
        timer->start(30);
        break;
    case 2 ://para los pajaros
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveSenoidal);
        break;
    case 3:// proyectil giran
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveParabolico);
        break;
    case 4:// balas
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveRecto);

    }
}

void obstaculos::moveeny(){
    int limitesuperior = 100;
    int limiteinferior = -100;
    int velocidad = 5;
    if (y() <= limitesuperior || y() >= limiteinferior){
     velocidad = -velocidad;
    }
    setY(y() + velocidad);
}

void obstaculos::moveSenoidal() {
    if (!disponible) return;
    int amplitud = 15;
    float frecuencia= 0.2;
    int limite = 30;
    int velX = 2;
    float y = amplitud * sin(t * frecuencia) + y0;
    t+=0.1;
    setPos(x() + velX, y); // Qt: actualiza posición del objeto en escena
    if(x()> limite || colision()){
        Goku->salud = ;
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

    if (y < 0 || colision()) {//modificar para que se detenga cuando hay colison o salga de la escena
        desactivar();
        return;
    }
}

void obstaculos::moveRecto() {
    int limite = 30;
    if (!disponible) return;

    int velocidad = 8;
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
