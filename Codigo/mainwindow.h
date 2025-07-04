#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QMainWindow>
#include <QKeyEvent>

class nivel1;
class nivel2;
class jugador;

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
    nivel1* Nivel1;
protected:
    void keyPressEvent(QKeyEvent* event) override;
    //nivel2* Nivel2;
};
#endif // MAINWINDOW_H
