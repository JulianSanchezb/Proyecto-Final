#ifndef NIVEL1_H
#define NIVEL1_H
#include <QGraphicsScene>
#include <QTimer>
#include <QProgressBar>
#include <QGraphicsProxyWidget>

class jugador;
class jefe;
class obstaculos;
class recolectables;

class nivel1 : public QObject
{
    QGraphicsScene *scene;
    QVector<obstaculos*> balas;
    QVector<obstaculos*> pajaros;
    QTimer* timerM;
    QTimer* timerP;
    QTimer* timerC;
    recolectables* esfera;
    recolectables* leche;
    QGraphicsTextItem* t1;
    QGraphicsTextItem* t2;
    QProgressBar* barraSalud;
    QGraphicsProxyWidget* proxy;
public:
    nivel1(jugador* goku);
    ~nivel1();
    jugador* Goku;
    obstaculos* camara;
    void creacion(QVector<obstaculos*>& contenedor, int cantidad, unsigned short int tipo);
    void mostrar_obstaculo(QVector<obstaculos *> contenedor, int cantidad, int x, int y);
    QGraphicsScene* obtenerEscena();
    void crearNube(const QString& rutaImagen, QPointF posicionInicial, float velocidad);

    //getter
    jugador* getGoku();
    recolectables* getleche();
    recolectables* getesferas();
    //Setters
    void setGoku(jugador* goku);
};


#endif // NIVEL1_H
