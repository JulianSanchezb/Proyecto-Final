#include "menu.h"
#include <QPixmap>
#include <QApplication>

menu::menu(){
    scene = new QGraphicsScene();

    // Fondo del menú
    QPixmap img(":/Multimedia/menu.jpg");
    scene->setBackgroundBrush(img);
    scene->setSceneRect(img.rect());

    spritesRoshi.append(QPixmap(":/Multimedia/MaestroRoshi/MaestroRoshi1.png"));
    spritesRoshi.append(QPixmap(":/Multimedia/MaestroRoshi/MaestroRoshi2.png"));
    spritesRoshi.append(QPixmap(":/Multimedia/MaestroRoshi/MaestroRoshi3.png"));

    roshi = scene->addPixmap(spritesRoshi[0]);
    roshi->setScale(7);
    roshi->setPos(2450, 1200);

    boton = new QPushButton("Start");
    proxy1 = scene->addWidget(boton);
    proxy1->setPos(1360, 853);
    proxy1->setScale(4);


    exit = new QPushButton("Salir");
    proxy2 = scene->addWidget(exit);
    proxy2->setPos(1360, 963);
    proxy2->setScale(4);

    connect(exit, &QPushButton::clicked, []() {
        QApplication::quit();
    });

    frameActual = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, [=]() {
        frameActual = (frameActual + 1) % spritesRoshi.size();
        roshi->setPixmap(spritesRoshi[frameActual]);
    });
    timer->start(360);
}

menu::~menu() {
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }

    if (scene) {
        delete scene;
        scene = nullptr;
    }

    if(exit){
        delete exit;
        exit = nullptr;
    }

    if(boton){
        delete boton;
        boton = nullptr;
    }
}

QGraphicsScene* menu::obtenerEscena(){
    return scene;
}

QPushButton* menu::getBoton(){
    return boton;
}

//Setters
void menu::setTimer(bool des){
    if(des){
        timer->start(360);
    }else{
        timer->stop();
    }
}
