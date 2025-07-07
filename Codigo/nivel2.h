#ifndef NIVEL2_H
#define NIVEL2_H
#include <QGraphicsScene>
class obstaculos;
class jugador;
class jefe;
class recolectables;

class nivel2 : public QObject
{
    QGraphicsScene *scene;
    QVector<obstaculos *> proyectiles;
    QTimer* timerP;
public:
    nivel2(jugador *goku);
    jugador* Goku;
    jefe* Giran;
    void mostrar_obstaculo(QVector<obstaculos *> &contenedor, int cantidad, int x, int y);
    void creacion(QVector<obstaculos*>& contenedor, int cantidad, unsigned short int tipo);
    //getter
    QGraphicsScene* obtenerEscena();
    jugador* getGoku();

    //setter
    void setGoku(jugador* goku);

};

#endif // NIVEL2_H
