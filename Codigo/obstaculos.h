#ifndef OBSTACULOS_H
#define OBSTACULOS_H
#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <QPainter>

class obstaculos: public QGraphicsItem
{
private:
    int posx;
    int posy;
    int velx;
    int vely;
    int g;
    int t;
    int ancho, alto;
public:
    obstaculos();
    void moveSenoidal();
    void moveParabolico();
    void moveRecto();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // OBSTACULOS_H
