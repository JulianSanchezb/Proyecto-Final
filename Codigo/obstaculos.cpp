#include "obstaculos.h"
using namespace std;

obstaculos::obstaculos(int x,int y, int velox,int veloy,int tiempo,int gravedad,int anchoi,int altoi,jugador* Gokui,unsigned short int tipo) {
    posx = x;
    posy = y;
    velx = velox;
    vely = veloy;
    t = tiempo;
    g = gravedad;
    ancho = anchoi;
    alto = altoi;
    Goku = Gokui;

    switch(tipo){
    case 1:
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &obstaculos::moveeny);
        timer->start(30);
        break;
    case 2 :
        break;
    case 3:
        break;

    }
}

void obstaculos::moveeny(){
    int limitesuperior = 100;
    int limiteinferior = -100;
    int velocidad = 5;
    if (y() <= limitesuperior || y() >= limiteinferior)
        velocidad = -velocidad;


    setY(y() + velocidad);
}

void obstaculos::moveSenoidal() {
    int amplitud = 15;
    int frecuencia= 0.1;
    int Tiempo = 0;
    float t = Tiempo * frecuencia;
    float y = amplitud * sin(t) + y();

    setPos(x(), y); // Qt: actualiza posición del objeto en escena
    //contadorTiempo++;
}

void obstaculos::moveParabolico() {
    t += 0.1; // incremento de tiempo
    double v0 = 5;
    // Movimiento parabólico
    double vx = v0 * qCos(angle);
    double vy = v0 * qSin(angle);

    double x = posx + vx * t;
    double y = posy + vy * t - 0.5 * g * t * t;

    if (y < 0) {//modificar para que se detenga cuando hay colison o salga de la escena
        timer->stop(); // detener cuando toca el suelo
        return;
    }

    // Mover la pelota (invertimos Y)
    setPos(x, 580 - y);
}

void obstaculos::moveRecto() {
    int velocidad = 8;
    setPos(x()+ velocidad, y());
}


QRectF obstaculos::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void obstaculos::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    //painter->setBrush(color); // usar el color actual
    painter->drawEllipse(0, 0, ancho, alto); // dibujo simple del fantasma
}
