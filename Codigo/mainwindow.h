#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QMainWindow>
#include <QKeyEvent>

class nivel1;
class nivel2;
class jugador;
class menu;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void cambiarEscena(short int Escena);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* escena;
    jugador* ptrG;
    QTimer* timerS;
    QTimer* timerN;
    QTimer* movimientoTimer;
    menu* Menu = nullptr;
    QGraphicsTextItem* t1;
    QGraphicsTextItem* t2;
    bool limitetiempo = false;
    nivel1* Nivel1 = nullptr;
    nivel2* Nivel2 = nullptr;
    unsigned short int tiponivel = 0;
    bool replay;
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
