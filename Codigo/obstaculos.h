#ifndef OBSTACULOS_H
#define OBSTACULOS_H
#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <QPainter>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
class jugador;

class obstaculos: public QGraphicsItem, public QObject
{
private:
    int posx;
    int posy;
    int velx;
    int vely;
    int g;
    int t;
    int ancho, alto;
    jugador* Goku;
    QTimer* timer;
    unsigned short tipo;
public:
    obstaculos(int x, int y, int velox, int veloy, int tiempo, int gravedad, int anchoi, int altoi, jugador *Gokui, unsigned short tipo);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

public slots:
    void moveeny();
    void moveSenoidal();
    void moveParabolico();
    void moveRecto();

};

#endif // OBSTACULOS_H
