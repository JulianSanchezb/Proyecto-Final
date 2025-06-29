#ifndef RECOLECTABLES_H
#define RECOLECTABLES_H
#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <QPainter>

class recolectables: public QGraphicsItem
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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // RECOLECTABLES_H
