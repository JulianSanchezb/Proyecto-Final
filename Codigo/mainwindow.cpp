#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jugador.h"
#include "nivel1.h"
#include "nivel2.h"
#include "recolectables.h"
#include "menu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    ptrG(new jugador(250, 1.5, 0, 100, 70, 215, 50, 5, 5)),
    timerS(new QTimer(this)),
    timerN(new QTimer(this)),
    tiponivel(0),
    replay(true)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);  // El MainWindow escucha teclas
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);  // Elimina interferencia

    Menu = new menu();

    QTimer::singleShot(0, this, [this]() {
        cambiarEscena(0);
    });

    connect(Menu->getBoton(), &QPushButton::clicked, this, [this]() {

        if (!Nivel1){
            Nivel1 = new nivel1(ptrG);
        }

        tiponivel = 1;

        ui->progressBar->setVisible(true);
        timerN->start(60000);
        timerS->start(200);
        cambiarEscena(tiponivel);
    });

    connect(timerN, &QTimer::timeout, this, [this]() {
        limitetiempo = true;
    });

    connect(timerS, &QTimer::timeout, this, [this]() {
        if(replay){
            ptrG->setSalud(250);
            ptrG->setEstado(0);
            ptrG->resetAnimtimer();
            replay = false;
        }
        ui->progressBar->setValue(ptrG->getSalud());

        if(ptrG->getSalud() <= 0 || limitetiempo){
            timerN->stop();
            QTimer::singleShot(3000, this, [this]() {
                if(limitetiempo){
                    tiponivel = 2;
                    if(Nivel1){
                    ptrG->setEnergia(Nivel1->getesferas()->getcontcol());
                    ptrG->setSaludables(Nivel1->getleche()->getcontcol());
                    }
                    if (!Nivel2){
                        Nivel2 = new nivel2(ptrG);
                    }
                }else if(ptrG->getSalud() <= 0){
                    replay = true;
                    tiponivel = 0;
                    ptrG->setPos(215,50);
                    if (ptrG->scene()){
                        ptrG->scene()->removeItem(ptrG);
                    }
                }
                if (timerS->isActive()){
                    timerS->stop();
                }
                if (Nivel1) {
                    delete Nivel1;
                    Nivel1 = nullptr;
                }

                cambiarEscena(tiponivel);
            });
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cambiarEscena(short Escena){
    switch(Escena){
    case 1:
        ptrG->setnivel(1);
        if(Nivel1){
        escena = Nivel1->obtenerEscena();
        ui->graphicsView->setScene(escena);
        }

        ui->graphicsView->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
        break;
    case 2:
        ptrG->setnivel(2);
        if (Nivel2){
            escena = Nivel2->obtenerEscena();
            ui->graphicsView->setScene(escena);
        }
        ui->graphicsView->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
        break;
    case 0:
        if (Menu) {
            escena = Menu->obtenerEscena();
            ui->graphicsView->setScene(escena);

            ui->graphicsView->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);

            ui->progressBar->setVisible(false);
        }
        break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (!ptrG) return;

    if(tiponivel == 1){
        switch (event->key()) {
        case Qt::Key_W:
            if(ptrG->y()>=0){
                ptrG->moveUp2();
            }
            break;
        case Qt::Key_S:
            if(ptrG->y()<=95){
                ptrG->moveDown();
            }
            break;
        case Qt::Key_A:
            if(ptrG->x()>=0){
                ptrG->moveLeftp();
            }
            break;
        case Qt::Key_D:
            if(ptrG->x()<=220){
                ptrG->moveRightp();
            }
            break;
        }

    }else if (tiponivel == 2){
        switch (event->key()) {
        case Qt::Key_W:
            if(ptrG->getGround()){
                ptrG->moveUp();
            }
            break;
        case Qt::Key_A:
            if(x() >= 3){
                ptrG->keysPressed.insert(Qt::Key_A);
                ptrG->moveLeft();
            }
            break;
        case Qt::Key_D:
            if(x() <= 420){
                ptrG->keysPressed.insert(Qt::Key_D);
                ptrG->moveRight();
            }
            break;
        }

        }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    if (!ptrG) return;

    // Solo queremos detener el movimiento si estamos en nivel 2
    if (tiponivel == 2) {
        ptrG->keysPressed.remove(event->key());

        if (!ptrG->keysPressed.contains(Qt::Key_A) && !ptrG->keysPressed.contains(Qt::Key_D)) {
            ptrG->detenerMovimiento();  // Solo detiene si ninguna tecla está presionada
        }

        if (event->key() == Qt::Key_W && ptrG->getGround()) {
            ptrG->setPixmap(ptrG->idleFrames[0]);  // Mostrar sprite en reposo tras salto
        }
    }
}

