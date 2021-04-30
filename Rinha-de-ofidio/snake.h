#ifndef SNAKE_H
#define SNAKE_H
#include <QGraphicsPixmapItem>
#include <math.h>
#include "bodypart.h"
using namespace std;

class Snake : public QObject
{

    Q_OBJECT
private:
    QMediaPlayer *bulletsound;
    QString tipo;
    void die();

public:
    bool isOpposite(string d);
    vector<BodyPart *> myBody;
    void reset()
    {
        isVivo = true;
        ready = false;
    }
    bool isVivo;
    Snake();
    Snake(QString t);

    void move(string decisao);

    bool ready;
    void addNew();
    ~Snake()
    {
        for (size_t i = 0; i < myBody.size(); i++)
        {
            delete myBody.at(i);
        }
    }
public slots:
    void move()
    {
        if (!ready)
            return;
        move(myBody.at(0)->lastAction);
    };
};

#endif // SNAKE_H
