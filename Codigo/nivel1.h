#ifndef NIVEL1_H
#define NIVEL1_H
#include <QGraphicsScene>
#include <QTimer>

class obstaculos;
class jugador;
class jefe;
class recolectables;

class nivel1 : public QObject
{
    QGraphicsScene *scene;
    QVector<obstaculos*> balas;
    QVector<obstaculos*> pajaros;
    QTimer* timerM;
    QTimer* timerP;
    recolectables* esfera;
    recolectables* leche;
public:
    nivel1(jugador* goku);
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
