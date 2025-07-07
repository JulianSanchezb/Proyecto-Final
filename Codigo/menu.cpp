#include "menu.h"
#include <QPixmap>

menu::menu(){
    scene = new QGraphicsScene();

    // Fondo del menú
    QPixmap img("C:/Users/Julian/Pictures/Saved Pictures/casa z.jpg");
    QGraphicsPixmapItem* fondo = scene->addPixmap(img);
    fondo->setZValue(-1); // Para que quede al fondo
    scene->setSceneRect(img.rect());


    boton = new QPushButton("Start");
    proxy1 = scene->addWidget(boton);
    proxy1->setPos(1406, 853);
    proxy1->setScale(4);
}

QGraphicsScene* menu::obtenerEscena(){
    return scene;
}

QPushButton* menu::getBoton(){
    return boton;
}
