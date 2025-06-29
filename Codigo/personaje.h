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
    int g;
    int t;
    unsigned short int ancho;
    unsigned short int alto;
    bool onGround;

public:
    int posx;
    int posy;
    int velx;
    int vely;
    personaje();
    void moveUp();
    void moveRight();
    void moveLeft();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setPosy(int y);
};

#endif // PERSONAJE_H
