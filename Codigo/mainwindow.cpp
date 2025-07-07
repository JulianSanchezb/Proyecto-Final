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
    t1(new QGraphicsTextItem()),
    t2(new QGraphicsTextItem()),
    tiponivel(0)

//Nivel2(nullptr)
{
    ui->setupUi(this);

    Menu = new menu();

    QTimer::singleShot(0, this, [this]() {
        cambiarEscena(0);  // Aquí sí funciona bien el fitInView
    });

    connect(Menu->getBoton(), &QPushButton::clicked, this, [this]() {
        if (!Nivel1){
            Nivel1 = new nivel1(ptrG);
        }

        if (Menu) {     //Libera la memoria reservada para la escena del menú
            delete Menu;
            Menu = nullptr;
        }

        tiponivel = 1;

        QTimer::singleShot(1000, this, [this]() {
            limitetiempo = true;
        });

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
                if(limitetiempo){
                    tiponivel = 2;
                    ptrG->setEnergia(Nivel1->getesferas()->getcontcol());
                    ptrG->setSaludables(Nivel1->getleche()->getcontcol());
                    if (Nivel1) {
                        delete Nivel1;
                        Nivel1 = nullptr;
                    }
                }else if(ptrG->getSalud() <= 0){
                    if (Nivel1) {
                        delete Nivel1;
                        Nivel1 = nullptr;
                    }
                    if (!Menu) {
                        Menu = new menu();
                    }
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
        escena = Nivel1->obtenerEscena();
        ui->graphicsView->setScene(escena);

        escena->addItem(t1);
        t1->setPos(195, 3);

        escena->addItem(t2);
        t2->setPos(170, 3);

        t1->setScale(0.5);
        t2->setScale(0.5);
        ui->graphicsView->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
        break;
    case 2:
        if (!Nivel2){
            Nivel2 = new nivel2(ptrG);
        }
        escena = Nivel2->obtenerEscena();
        ui->graphicsView->setScene(escena);

        //escena->addItem(t1);
        //t1->setPos(195, 3);

        //escena->addItem(t2);
        //t2->setPos(170, 3);

        //t1->setScale(0.5);
        //t2->setScale(0.5);
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
