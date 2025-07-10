#ifndef OBSTACULOS_H
#define OBSTACULOS_H
#include <QObject>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QtMath>

class jugador;
class jefe;

class obstaculos: public QGraphicsPixmapItem, public QObject
{
private:
    float posx;
    float posy;
    float velx;
    float vely;
    float y0 ;
    float x0 ;
    float g;
    float t ;
    int limiteinferior;
    int limitesuperior;
    int limiteizquierda;
    int limitederecha;
    int ancho, alto;
    jugador* Goku;
    jefe* Guiran;
    QTimer* timer;
    unsigned short tipo;
    bool disponible;
    QVector<QPixmap> frames; // Almacena los distintos sprites
    int frameIndex;
    int frameCount;
public:
    int direccion = 0;
    obstaculos(float x, float y, float velox, float veloy, float tiempo, float gravedad, int anchoi, int altoi, jugador *Gokui, unsigned short tipo);
    ~obstaculos();
    QVector<QPixmap> idleFrames;
    QVector<QPixmap> shootFrames;
    bool disparando = false;
    void animarDisparo();
    void desactivar();
    void activar(QPointF posicion, int tiempo);
    bool colision();
    bool getdisponible();

    bool setDisponible(bool tipo);
    void setGuiran(jefe* g);
public slots:
    void moveeny();
    void moveSenoidal();
    void moveParabolico();
    void moveRecto();
    void moveEsfera();
};

#endif // OBSTACULOS_H
