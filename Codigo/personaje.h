#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <QPainter>

class personaje : public QGraphicsItem
{
private:
    unsigned short int salud;
    unsigned short int vel;
    int posx;
    int posy;
    unsigned short int ancho;
    unsigned short int alto;
    bool tipoDano;

public:
    personaje();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // PERSONAJE_H
