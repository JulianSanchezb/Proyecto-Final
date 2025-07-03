#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QMainWindow>

class nivel1;
class nivel2;

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
    nivel1* Nivel1;
    //nivel2* Nivel2;
};
#endif // MAINWINDOW_H
