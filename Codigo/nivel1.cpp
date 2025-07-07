#include "nivel1.h"
#include "obstaculos.h"
#include "jugador.h"
#include "recolectables.h"

nivel1::nivel1(jugador *goku): scene(new QGraphicsScene()),
    Goku(goku),
    camara(new obstaculos(100,1, 0, 5, 0, 0, 25, 25, Goku, 1)),
    timerM(new QTimer(this)),
    timerP(new QTimer(this))
{
    creacion(balas,3,4);
    creacion(pajaros,2,2);

    esfera = new recolectables(50, 50, 1, 1, 10, 10, Goku);
    scene->addItem(esfera);
    esfera->setZValue(20);
    esfera->setParentItem(nullptr);  // Si quieres que sea independiente
    esfera->setVisible(false);
    esfera->setScale(0.3);

    leche = new recolectables(100, 20, 1, 2, 10, 10, Goku);
    leche->setParentItem(nullptr);  // Si quieres que sea independiente
    scene->addItem(leche);
    leche->setZValue(20);
    leche->setVisible(false);
    leche->setScale(0.3);



    QPixmap img(":/Multimedia/background-1.png");
    //QGraphicsPixmapItem* fondo = scene->addPixmap(img);
    //scene->setZValue(-1); // Para que quede al fondo
    //scene->setSceneRect(img.rect());
    scene->setBackgroundBrush(img);
    scene->setSceneRect(img.rect());

    //scene->setSceneRect(0, 0, 254, 125);

    QPixmap salud(":/Multimedia/salud.png");
    QPixmap saludEscalada = salud.scaled(45,30);  // Aquí sí se guarda la imagen escalada
    QGraphicsPixmapItem* vida = scene->addPixmap(saludEscalada);
    vida->setPos(210,-5); // Posición exacta en la escena
    vida->setZValue(10);

    crearNube(":/Multimedia/nubes.png",QPointF(1,1),1);
    scene->addItem(Goku);
    Goku->setPos(215,50);
    Goku->setScale(0.5);
    scene->addItem(camara);
    camara->setPos(1,1);


    QPixmap imgEsfera(":/Multimedia/esfera1.png");
    QGraphicsPixmapItem* esfera = scene->addPixmap(imgEsfera);
    esfera->setPos(180, 3);
    esfera->setScale(0.3);  // si es muy grande
    esfera->setZValue(20);   // encima del fondo pero debajo de personajes si quieres

    // Leche decorativa
    QPixmap imgLeche(":/Multimedia/leche.png");
    QGraphicsPixmapItem* leche = scene->addPixmap(imgLeche);
    leche->setPos(160, 3);
    leche->setScale(0.3);
    leche->setZValue(20);



    connect(timerM, &QTimer::timeout, this, [=]() {
        camara->animarDisparo();
        mostrar_obstaculo(balas, 3, 18, 18);
    });
    timerM->start(2000);
    connect(timerP, &QTimer::timeout, this, [=]() {
        mostrar_obstaculo(pajaros, 2, 1, 30);
    });
    timerP->start(4000);
}

// hay que agregar todo a la escena
//revisar al final que va a ser camara


void nivel1::mostrar_obstaculo(QVector<obstaculos*> contenedor, int cantidad, int x, int y) {// puede ser plantilla para pajaros y balas.
    QPointF posicion = QPointF(x,y);
    for (int i = 0; i < cantidad; ++i) {
        if (!contenedor[i]->getdisponible()){
            QPointF origen = camara->pos() + posicion;  // punto desde donde sale la bala, modificar 200 y 50
            contenedor[i]->activar(origen,200);// para QpointF puede pasarse como parametro para que funicone para pajaros tambien
            break;
        }
    }
}

void nivel1::creacion(QVector<obstaculos*>& contenedor, int cantidad, unsigned short int tipo) {
    for (int i = 0; i < cantidad; ++i) {
        obstaculos* obj = new obstaculos(0, 0, 0, 0, 0, 0, 15, 15, Goku, tipo);
        contenedor.append(obj);
        scene->addItem(obj);
        obj->desactivar();
    }
}

void nivel1::crearNube(const QString& rutaImagen, QPointF posicionInicial, float velocidad)
{
    // Crear nube con la imagen
    QPixmap pixmap(rutaImagen);
    QGraphicsPixmapItem* nube = scene->addPixmap(pixmap);
    nube->setPos(posicionInicial);
    nube->setZValue(-0.5); // Entre fondo y personajes

    // Crear temporizador para mover la nube
    QTimer* nubeTimer = new QTimer(this);
    connect(nubeTimer, &QTimer::timeout, this, [=]() {
        nube->moveBy(velocidad, 0);

        // Si sale de la escena por la derecha, vuelve a empezar por la izquierda
        if (nube->x() > 20) {
            nube->setX(-nube->boundingRect().width());
        }
    });

    nubeTimer->start(35); // Mover cada 30 ms
}



QGraphicsScene* nivel1::obtenerEscena(){
    return scene;
}

//Getter
jugador* nivel1::getGoku(){
    return Goku;
}

recolectables* nivel1::getesferas(){
    return esfera;
}

recolectables* nivel1::getleche(){
    return leche;
}

//Setters
void nivel1::setGoku(jugador* goku){
    Goku = goku;
}


