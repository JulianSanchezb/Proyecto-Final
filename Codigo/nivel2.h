#ifndef NIVEL2_H
#define NIVEL2_H
#include <QGraphicsScene>
#include <QProgressBar>
#include <QGraphicsProxyWidget>

class jugador;
class jefe;
class obstaculos;

class nivel2 : public QObject
{
    QGraphicsScene *scene;
    QVector<obstaculos *> proyectiles;
    QVector<obstaculos *> esferas;
    QTimer* timerP;
    QGraphicsTextItem* t1;
    QGraphicsTextItem* t2;
    QProgressBar* barraSalud;
    QGraphicsProxyWidget* proxy1;
    QProgressBar* barraGiran;
    QGraphicsProxyWidget* proxy2;
    bool variable = true;
public:
    nivel2(jugador *goku);
    ~nivel2();
    jugador* Goku;
    jefe* Giran;
    void mostrar_obstaculo(QVector<obstaculos *> &contenedor, int cantidad, int x, int y, int direccion, bool tipo);
    void creacion(QVector<obstaculos*>& contenedor, int cantidad, unsigned short int tipo);
    //getter
    QGraphicsScene* obtenerEscena();
    jugador* getGoku();
    jefe* getGiran();
    //setter
    void setGoku(jugador* goku);
    void setT1();
    void setT2();
};

#endif // NIVEL2_H
