#ifndef FOOD_H
#define FOOD_H
//#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

#include <iostream>

using namespace std;

class Food : public QObject, public QGraphicsPixmapItem
{
public:
    Food(QGraphicsPixmapItem *parent = 0);
    ~Food()
    {
    };
};

#endif // FOOD_H
