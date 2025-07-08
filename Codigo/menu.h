#ifndef MENU_H
#define MENU_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QObject>
#include <QTimer>
#include <QVector>

class menu : public QObject  // ← Heredar de QObject
{
    Q_OBJECT
private:
    QGraphicsScene* scene;
    QPushButton* boton;
    QGraphicsProxyWidget* proxy1;
    QVector<QPixmap> spritesRoshi;
    QGraphicsPixmapItem* roshi;   // El objeto gráfico que se ve en la escena
    QTimer* timer;
    short int frameActual;
public:
    menu();
    ~menu();
    QGraphicsScene* obtenerEscena();
    QPushButton* getBoton();
    //Setters
    void setTimer(bool des);
};

#endif // MENU_H
