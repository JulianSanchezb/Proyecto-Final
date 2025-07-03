#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jugador.h"
#include "nivel1.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,Nivel1(new nivel1())
    //Nivel2(nullptr)
{
    ui->setupUi(this);

    jugador goku(100, 1.5, 0, 10,10, 50, 50, 20, 20);
    jugador *ptrG = &goku;
    Nivel1->setGoku(ptrG);
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
