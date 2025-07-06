#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jugador.h"
#include "nivel1.h"
#include "recolectables.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    ptrG(new jugador(250, 1.5, 0, 100, 70, 215, 50, 5, 5, 1)),
    timerS(new QTimer(this)),
    t1(new QGraphicsTextItem()),
    t2(new QGraphicsTextItem())


//Nivel2(nullptr)
{
    ui->setupUi(this);

    // Crear la escena del menú
    //menu = new QGraphicsScene(this);

    // Cargar y escalar la imagen de fondo al tamaño del graphicsView
    //QPixmap img(":/Multimedia/menu.png");
    //QPixmap imgEscalado = img.scaled(ui->graphicsView->size(), Qt::KeepAspectRatioByExpanding);

    // Agregar el fondo escalado a la escena
    //QGraphicsPixmapItem* fondo = menu->addPixmap(imgEscalado);
    //fondo->setZValue(-1);

    // Ajustar el rectángulo de la escena al tamaño del gráfico
    //menu->setSceneRect(fondo->boundingRect());

    // Establecer la escena en el graphicsView
    //ui->graphicsView->setScene(menu);
    //ui->graphicsView->fitInView(menu->sceneRect(), Qt::KeepAspectRatio);


    ui->progressBar->setVisible(false);
    connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
        if (!Nivel1)
            Nivel1 = new nivel1(ptrG);

        tiponivel = 1;

        QTimer::singleShot(182000, this, [this]() {
            limitetiempo = true;
        });

        ui->pushButton->setVisible(false);
        ui->progressBar->setVisible(true);
        cambiarEscena(tiponivel);
        timerS->start(200);
        connect(timerS, &QTimer::timeout, this, [=]() {
            ui->progressBar->setValue(ptrG->getSalud());
            if (Nivel1 && Nivel1->getesferas()) {
                if(Nivel1->getesferas()->getvisibilidad()){
                t1->setPlainText(QString::number(Nivel1->getesferas()->getcontcol()));

                }
                if(Nivel1->getleche()->getvisibilidad()){
                t2->setPlainText(QString::number(Nivel1->getleche()->getcontcol()));
                }
            }
            if(ptrG->getSalud() <= 0 || limitetiempo){
                timerS->stop();
                if (Nivel1) {
                    delete Nivel1;
                    Nivel1 = nullptr;
                }
                if(limitetiempo){
                    tiponivel = 2;
                }else{
                    tiponivel = 0;
                }
                cambiarEscena(tiponivel);
            }
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cambiarEscena(short Escena){
    switch(Escena){
    case 1:
        //ui->graphicsView->setBackgroundBrush(brush);
        escena = Nivel1->obtenerEscena();
        ui->graphicsView->setScene(escena);
        //escena->setSceneRect(30,20,100,50);

        escena->addItem(t1);
        t1->setPos(195, 3);

        escena->addItem(t2);
        t2->setPos(170, 3);

        t1->setScale(0.5);
        t2->setScale(0.5);

        break;
    case 2:
        break;
    case 0:
        ui->graphicsView->setScene(menu);
        ui->progressBar->setVisible(false);
        ui->pushButton->setVisible(true);
        break;
    }
    // Ajustar la vista para escalar automáticamente al nuevo contenido
    ui->graphicsView->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (!Nivel1) return;
    jugador* Goku = Nivel1->Goku;  // Acceso directo al puntero Goku
    if (!Goku) return;
    if(tiponivel == 1){
        switch (event->key()) {
        case Qt::Key_W:
            if(Goku->y()>=0){
                Goku->moveUp2();
            }
            break;
        case Qt::Key_S:
            if(Goku->y()<=95){
                Goku->moveDown();
            }
            break;
        case Qt::Key_A:
            if(Goku->x()>=0){
                Goku->moveLeft();
            }
            break;
        case Qt::Key_D:
            if(Goku->x()<=220){
                Goku->moveRight();
            }
            break;
        }

    }else if (tiponivel == 2){
        switch (event->key()) {
        case Qt::Key_W:
            if(Goku->y()<=95){
                Goku->moveUp2();
            }
            break;
        case Qt::Key_A:
            if(Goku->x()>=0){
                Goku->moveLeft();
            }
            break;
        case Qt::Key_D:
            if(Goku->x()<=220){
                Goku->moveRight();
            }
            break;
        }

        }
}
