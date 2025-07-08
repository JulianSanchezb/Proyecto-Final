#ifndef RECOLECTABLES_H
#define RECOLECTABLES_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>
#include <QPointF>
class jugador;

class recolectables: public QGraphicsPixmapItem, public QObject
{
private:
    int posx;
    int posy;
    unsigned short int aporte;
    unsigned short int tipo;
    int ancho, alto;
    jugador* prota;
    QTimer* timer;
    QTimer* timercol;
    QGraphicsPixmapItem* sprite;
    int contador;
    QString nombreSprite;
    int contcol  = 0;
public:
    recolectables(int x, int y, unsigned short int cantidad, unsigned short int type,int w, int h, jugador* Goku);
    ~recolectables();
    bool visible = false;
    //QRectF boundingRect() const override;
    bool colision();
    unsigned short getAporte();
    void posicion(int x);
    int getcontcol();
    bool getvisibilidad();
};

#endif // RECOLECTABLES_H
