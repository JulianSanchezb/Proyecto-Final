#include "recolectables.h"
#include "jugador.h"
recolectables::recolectables(int x, int y, unsigned short cantidad, unsigned short type,
                             int w, int h, jugador* Goku)
: QGraphicsPixmapItem(nullptr)
{
    posx = x;
    posy = y;
    aporte = cantidad;
    tipo = type;
    ancho = w;
    alto = h;
    prota = Goku;
    timer = new QTimer(this);
    timercol = new QTimer(this);

    switch(tipo){
    case 1://esferas
        contador = 1;
        connect(timer, &QTimer::timeout, this, [=]() mutable{
            QString nombreSprite = QString(":/Multimedia/esfera%1.png").arg(contador);
            setPixmap(QPixmap(nombreSprite));
            setVisible(true);
            visible=true;
            timer->stop();
            posicion(0);
            connect(timercol, &QTimer::timeout, this, &recolectables::colision);
            timercol->start(20);
            QTimer::singleShot(5000, this, [=]() {
                timer->start();
                setVisible(false);
                visible = false;
            });
            contador = (contador % 7) + 1;
        });
        timer->start(20000);
        break;
    case 2:
        setPixmap(QPixmap(":/Multimedia/leche.png"));
        connect(timer, &QTimer::timeout, this, [=]() {
            setVisible(true);
            visible = true;
            timer->stop();
            posicion(20);
            connect(timercol, &QTimer::timeout, this, &recolectables::colision);
            timercol->start(20);
            QTimer::singleShot(5000, this, [=]() {
                timer->start();
                setVisible(false);
                visible = false;
            });
        });
        timer->start(12000);
        break;
    }
}

recolectables::~recolectables() {
    if (timer) {
        timer->stop();
    }

    if (timercol) {
        timercol->stop();
    }
}

void recolectables::posicion(int x){

    static int paso = 0;  // estatico para que se mantenga en las llamadas

    QVector<QPointF> posiciones = {
        QPointF(50 + x, 50),
        QPointF(100 + x, 78),
        QPointF(150 + x, 95),
        QPointF(200 + x, 50),
        QPointF(210 + x, 69),
        QPointF(125 + x, 80),
        QPointF(70 + x, 50)
    };

    setPos(posiciones[paso]);

    paso = (paso + 1) % posiciones.size();
}

bool recolectables::colision(){
    if(collidesWithItem(prota)){
        setPos(500,500);
        setVisible(false);
        contcol++;
        return true;
    }else{
        return false;
    }
}

unsigned short int recolectables::getAporte(){
    return aporte;
}

int recolectables::getcontcol(){
    return contcol;
}

bool recolectables::getvisibilidad(){
    return visible;
}
