#include "menu.h"
#include <QPixmap>

menu::menu(){
    scene = new QGraphicsScene();

    // Fondo del menú
    QPixmap img(":/Multimedia/menu.jpg");
    /*
    QGraphicsPixmapItem* fondo = scene->addPixmap(img);
    fondo->setZValue(-1); // Para que quede al fondo*/
    scene->setBackgroundBrush(img);
    scene->setSceneRect(img.rect());

    spritesRoshi.append(QPixmap(":/Multimedia/MaestroRoshi/MaestroRoshi1.png"));
    spritesRoshi.append(QPixmap(":/Multimedia/MaestroRoshi/MaestroRoshi2.png"));
    spritesRoshi.append(QPixmap(":/Multimedia/MaestroRoshi/MaestroRoshi3.png"));

    roshi = scene->addPixmap(spritesRoshi[0]);  // Primer frame
    roshi->setScale(7);
    roshi->setPos(2450, 1200);

    boton = new QPushButton("Start");
    proxy1 = scene->addWidget(boton);
    proxy1->setPos(1360, 853);
    proxy1->setScale(4);

    frameActual = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        frameActual = (frameActual + 1) % spritesRoshi.size();
        roshi->setPixmap(spritesRoshi[frameActual]);
    });
    timer->start(360);
}

QGraphicsScene* menu::obtenerEscena(){
    return scene;
}

QPushButton* menu::getBoton(){
    return boton;
}
