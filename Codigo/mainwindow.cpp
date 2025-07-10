#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jugador.h"
#include "jefe.h"
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

    movimientoTimer = new QTimer(this);
    connect(movimientoTimer, &QTimer::timeout, this, [=]() {
        if (tiponivel == 2 && ptrG) {
            ptrG->actualizarMovimiento();
        }
    });
    movimientoTimer->start(30);


    Menu = new menu();

    QTimer::singleShot(0, this, [this]() {
        cambiarEscena(0);
    });

    connect(Menu->getBoton(), &QPushButton::clicked, this, [this]() {

        if (!Nivel1){
            Nivel1 = new nivel1(ptrG);
        }

        tiponivel = 1;
      
        timerN->start(184000);
        if(!timerS->isActive()){
            timerS->start(200);
        }
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

        if(ptrG->getSalud() <= 0 || limitetiempo){

            timerN->stop();
            QTimer::singleShot(3000, this, [this]() {

                if(limitetiempo){
                    tiponivel = 2;
                    if(Nivel1){
                    ptrG->setEnergia(Nivel1->getesferas()->getcontcol());
                    ptrG->setSaludables(Nivel1->getleche()->getcontcol());
                    }
                    if (Nivel1) {
                        delete Nivel1;
                        Nivel1 = nullptr;
                    }

                    if (!Nivel2){
                        Nivel2 = new nivel2(ptrG);
                    }

                    if(Nivel2->getGiran()->getSalud() <= 0 || ptrG->getSalud() <= 0){
                        QTimer::singleShot(3000, this, [this](){

                            replay = true;
                            limitetiempo = false;
                            ptrG->setSaludables(0);
                            ptrG->setEnergia(0);
                            tiponivel = 0;
                            if(Nivel2){
                                delete Nivel2;
                                Nivel2 = nullptr;
                            }
                            cambiarEscena(tiponivel);
                        });
                    }
                }else if(ptrG->getSalud() <= 0){
                    if (Nivel1) {
                        delete Nivel1;
                        Nivel1 = nullptr;
                    }
                    replay = true;
                    tiponivel = 0;
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
        Menu->setTimer(0);
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
            Menu->setTimer(1);
            escena = Menu->obtenerEscena();
            ui->graphicsView->setScene(escena);

            ui->graphicsView->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
        }
        break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (!ptrG) return;

    if(tiponivel == 1){
        switch (event->key()) {
        case Qt::Key_W:
            if(ptrG->y()>=0 && ptrG->getSalud() > 0 && !limitetiempo){
                ptrG->moveUp1();
            }
            break;
        case Qt::Key_S:
            if(ptrG->y()<=95 && ptrG->getSalud() > 0 && !limitetiempo){
                ptrG->moveDown();
            }
            break;
        case Qt::Key_A:
            if(ptrG->x()>=0 && ptrG->getSalud() > 0 && !limitetiempo){
                ptrG->moveLeft1();
            }
            break;
        case Qt::Key_D:
            if(ptrG->x()<=220 && ptrG->getSalud() > 0 && !limitetiempo){
                ptrG->moveRight1();
            }
            break;
        }

    }else if (tiponivel == 2){
        if (!event->isAutoRepeat()) {
            ptrG->keysPressed.insert(event->key());
        }

        switch (event->key()) {
            case Qt::Key_W:
                if (ptrG->getGround()&& ptrG->getSalud() > 0) {
                    ptrG->moveUp();
                }
                break;
            case Qt::Key_R:
                if (ptrG->getSaludables() > 0 && ptrG->getGround()) {
                    ptrG->consumir(1);
                    Nivel2->setT1();
                }
                break;
            case Qt::Key_Q:
                if (ptrG->getEnergia() > 0 && !ptrG->especial && ptrG->getGround() && ptrG->getSalud() > 0) {
                    ptrG->ataqueEspecial();
                    Nivel2->setT2();
                }
                break;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    if (!ptrG) return;

    if (tiponivel == 2) {
        if (!event->isAutoRepeat()) {
            ptrG->keysPressed.remove(event->key());
        }

        if (event->key() == Qt::Key_W && ptrG->getGround()) {
            ptrG->setPixmap(ptrG->idleFrames[0]);  // Sprite en reposo
        }
    }
}

