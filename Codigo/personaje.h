#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QObject>
#include <QGraphicsItem>

class personaje : public QObject, public QGraphicsPixmapItem
{
private:
    short int salud;
    float g;
    float t;
    unsigned short int ancho;
    unsigned short int alto;
    bool onGround;
public:
    personaje();
    QTimer* timer;
    QVector<QPixmap> frames;
    int frameIndex;
    int frameCount;
    QVector<QPixmap> idleFrames;
    QVector<QPixmap> hitFrames;
    float posx;
    float posy;
    float velx;
    float vely;
    virtual void moveUp();
    virtual void moveRight();
    virtual void moveLeft();

    //Getters
    short int getSalud();
    float getPosx();
    float getPosy();
    float getGravedad();
    unsigned short int getAncho();
    unsigned short int getAlto();
    float getTiempo();
    bool getGround();

    //Setters
    void setSalud(short int s);
    void setPosx(float x);
    void setPosy(float y);
    void setVelx(float x);
    void setVely(float y);
    void setGravedad(float gr);
    void setAncho(unsigned short int an);
    void setAlto(unsigned short int al);
    void setTiempo(float tiempo);
    void setGround(bool ground);
};

#endif // PERSONAJE_H
