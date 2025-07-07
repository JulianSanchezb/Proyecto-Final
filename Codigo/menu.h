#ifndef MENU_H
#define MENU_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class menu
{
private:
    QGraphicsScene* scene;
    QPushButton* boton;
    QGraphicsProxyWidget* proxy1;
public:
    menu();
    QGraphicsScene* obtenerEscena();
    QPushButton* getBoton();
};

#endif // MENU_H
