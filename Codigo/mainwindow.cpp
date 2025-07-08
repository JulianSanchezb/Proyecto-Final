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
    ptrG(new jugador(250, 1.5, 0, 100, 70, 215, 50, 5, 5, 1)),
    timerS(new QTimer(this)),
    timerN(new QTimer(this)),
    tiponivel(0),
    replay(true)

//Nivel2(nullptr)
{
    ui->setupUi(this);

    Menu = new menu();

    QTimer::singleShot(0, this, [this]() {
        cambiarEscena(0);
    });

    connect(Menu->getBoton(), &QPushButton::clicked, this, [this]() {

        if (!Nivel1){
            Nivel1 = new nivel1(ptrG);
            //qDebug()<<"Entro";
        }

        tiponivel = 1;

        ui->progressBar->setVisible(true);
        timerN->start(150000);
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
                }else if(ptrG->getSalud() <= 0){
                    replay = true;
                    tiponivel = 0;
                    ptrG->setPos(215,50);
                }
                if (timerS->isActive()) {
                    timerS->stop();
                }
                if (ptrG->scene()) {
                    ptrG->scene()->removeItem(ptrG);
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
        if(Nivel1){
        escena = Nivel1->obtenerEscena();

        ui->graphicsView->setScene(escena);
        }
        ui->graphicsView->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
        break;
    case 2:
        if (!Nivel2){
            Nivel2 = new nivel2(ptrG);
        }
        escena = Nivel2->obtenerEscena();
        ui->graphicsView->setScene(escena);
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
