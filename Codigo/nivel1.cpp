#include "nivel1.h"
#include "obstaculos.h"
#include "jugador.h"
#include "recolectables.h"

nivel1::nivel1(jugador *goku): scene(new QGraphicsScene()),
    Goku(goku),
    camara(new obstaculos(100,1, 0, 5, 0, 0, 25, 25, Goku, 1)),
    timerM(new QTimer(this)),
    timerP(new QTimer(this)),
    timerC(new QTimer(this))
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

    t1 = new QGraphicsTextItem;
    scene->addItem(t1);
    t1->setPos(195, 3);

    t2 = new QGraphicsTextItem;
    scene->addItem(t2);
    t2->setPos(170, 3);

    t1->setScale(0.5);
    t2->setScale(0.5);

    barraSalud = new QProgressBar();
    barraSalud->setRange(0, 500);
    barraSalud->setTextVisible(0);
    barraSalud->setStyleSheet(
        "QProgressBar {"
        "  border: 2px solid transparent;"
        "  border-radius: 1px;"
        "  text-align: center;"
        "  background-color: transparent;"
        "}"
        "QProgressBar::chunk {"
        "  background-color: red;"
        "  width: 2px;"
        "}"
        );
    barraSalud->setValue(Goku->getSalud());
    barraSalud->setFixedSize(34,7);

    proxy = scene->addWidget(barraSalud);
    proxy->setZValue(10);
    proxy->setPos(219, 8);

    QPixmap img(":/Multimedia/background-1.png");
    scene->setBackgroundBrush(img);
    scene->setSceneRect(img.rect());

    QPixmap salud(":/Multimedia/salud.png");
    QPixmap saludEscalada = salud.scaled(45,30);  // Aquí sí se guarda la imagen escalada
    QGraphicsPixmapItem* vida = scene->addPixmap(saludEscalada);
    vida->setPos(210,-5); // Posición exacta en la escena
    vida->setZValue(10);

    crearNube(":/Multimedia/nubes.png",QPointF(1,1),1);
    scene->addItem(Goku);
    Goku->setPos(215,50);
    Goku->setScale(0.5);
    Goku->setVelx(5);
    Goku->setVely(5);
    scene->addItem(camara);
    camara->setPos(1,1);

    QPixmap imgEsfera(":/Multimedia/esfera1.png");
    QGraphicsPixmapItem* esfera = scene->addPixmap(imgEsfera);
    esfera->setPos(180, 3);
    esfera->setScale(0.3);
    esfera->setZValue(20);

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

    connect(timerC, &QTimer::timeout, this, [=]() {
        if (getesferas()->getvisibilidad()) {
            t1->setPlainText(QString::number(getesferas()->getcontcol()));
        }
        if (getleche()->getvisibilidad()) {
            t2->setPlainText(QString::number(getleche()->getcontcol()));
        }
        barraSalud->setValue(Goku->getSalud());
    });
    timerC->start(500);
}

nivel1::~nivel1() {
    if (timerM) {
        timerM->stop();
        delete timerM;
        timerM = nullptr;
    }
    if (timerP) {
        timerP->stop();
        delete timerP;
        timerP = nullptr;
    }
    if (timerC) {
        timerC->stop();
        delete timerC;
        timerC = nullptr;
    }

    for (auto* const& b : balas) {
        delete b;
    }
    balas.clear();

    for (auto* const& p : pajaros) {
        delete p;
    }
    pajaros.clear();

    delete esfera;
    esfera = nullptr;

    delete leche;
    leche = nullptr;

    delete camara;
    camara = nullptr;

    if (proxy) {
        delete proxy;
        proxy = nullptr;
    }

    if (t1) {
        delete t1;
        t1 = nullptr;
    }

    if (t2) {
        delete t2;
        t2 = nullptr;
    }

    if (scene) {
        scene->clear();  // Elimina los items de la escena
        delete scene;
        scene = nullptr;
    }
}

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


