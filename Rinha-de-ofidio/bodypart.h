#ifndef BODYPART_H
#define BODYPART_H
//#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

#include <iostream>

using namespace std;

class BodyPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BodyPart(QGraphicsPixmapItem *parent = 0);
    string lastAction;
    ~BodyPart()
    {
        prepareGeometryChange();
    }
    bool move(string decisao);
};
#endif // BODYPART_H
