#ifndef OBSTACULOS_H
#define OBSTACULOS_H
#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <QPainter>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QtMath>
class jugador;

class obstaculos: public QGraphicsPixmapItem, public QObject
{
private:
    float posx;
    float posy;
    float velx;
    float vely;
    float y0;
    float g;
    float t;
    int limiteinferior;
    int limitesuperior;// mirar si definir los limites de la escena en el nivel de manera publica para poder acceder a ellos
    int limiteizquierda;
    int limitederecha;
    int ancho, alto;
    jugador* Goku;
    QTimer* timer;
    unsigned short tipo;
    bool disponible;
public:
    obstaculos(float x, float y, float velox, float veloy, float tiempo, float gravedad, int anchoi, int altoi, jugador *Gokui, unsigned short tipo);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void desactivar();
    void activar(QPointF posicion, int tiempo);
    bool colision();
    bool getdisponible();
public slots:
    void moveeny();
    void moveSenoidal();
    void moveParabolico();
    void moveRecto();

};

#endif // OBSTACULOS_H
