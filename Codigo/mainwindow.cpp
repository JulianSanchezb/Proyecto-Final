#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jugador.h"
#include "nivel1.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    ptrG(new jugador(100, 1.5, 0, 64, 64, 50, 50, 5, 5, 1))
    ,Nivel1(new nivel1(ptrG))
//Nivel2(nullptr)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
        cambiarEscena(1);
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
        break;
    case 2:
        break;
    case 3:
        break;
    }
    // Ajustar la vista para escalar automáticamente al nuevo contenido
    ui->graphicsView->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (!Nivel1) return;
    jugador* Goku = Nivel1->Goku;  // Acceso directo al puntero Goku
    if (!Goku) return;

    switch (event->key()) {
    case Qt::Key_W:
        Goku->moveUp2();
        break;
    case Qt::Key_S:
        Goku->moveDown();
        break;
    case Qt::Key_A:
        Goku->moveLeft();
        break;
    case Qt::Key_D:
        Goku->moveRight();
        break;
    }
}
