#ifndef RECOLECTABLES_H
#define RECOLECTABLES_H
#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <QPainter>

class recolectables: public QGraphicsPixmapItem, public QObject
{
private:
    int posx;
    int posy;
    unsigned short int aporte;
    unsigned short int tipo;
    int ancho, alto;
public:
    recolectables();
    QRectF boundingRect() const override;
};

#endif // RECOLECTABLES_H
