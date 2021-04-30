#include "snake.h"
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
#include <stdlib.h>
#include <iostream>
#include <QPointF >
using namespace std;
//#include "bullet.h"
//#include "enemy.h"

#include "food.h"
Snake::Snake()
{
}
Snake::Snake(QString t)
{
    tipo = t;
    isVivo = true;
    ready = false;
    BodyPart *p = new BodyPart();
    p->lastAction = "Left";
    QString image;

    p->setPixmap(QPixmap("://images/" + tipo + "Left.png"));
    p->setPos(32 * 4 + floor(32 * (rand() % 12)), 32 * 4 + floor(32 * (rand() % 12)));
    myBody.emplace_back(p);
}
void Snake::die()
{
    isVivo = false;
}
bool Snake::isOpposite(string d)
{
    if (d == "Up" && myBody.at(0)->lastAction == "Down")
        return true;
    if (d == "Down" && myBody.at(0)->lastAction == "Up")
        return true;
    if (d == "Left" && myBody.at(0)->lastAction == "Right")
        return true;
    if (d == "Right" && myBody.at(0)->lastAction == "Left")
        return true;
    return false;
}
void Snake::move(string decisao)
{
    if (!ready || isOpposite(decisao))
        return;

    vector<string> ant;

    //cout << endl;
    for (size_t i = myBody.size() - 1; i > 0; i--)
    {
        myBody.at(i)->setPos(myBody.at(i - 1)->pos());
    }
    myBody.at(0)->lastAction = decisao;
    isVivo = myBody.at(0)->move(decisao);
    myBody.at(0)->setPixmap(QPixmap("://images/" + tipo + QString::fromStdString(decisao) + ".png"));
    QList<QGraphicsItem *> colliding_item = myBody.at(0)->collidingItems();
    for (int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if (typeid(*(colliding_item[i])) == typeid(BodyPart))
        {
            die();
        }
    }
}
void Snake::addNew()
{
    string lastA = myBody.at(myBody.size() - 1)->lastAction;
    QPointF lastP = myBody.at(myBody.size() - 1)->pos();
    BodyPart *p = new BodyPart();

    p->setPixmap(QPixmap("://images/" + tipo + "Body.png"));
    p->setPos(lastP);
    p->lastAction = lastA;
    p->setFlag(QGraphicsItem::ItemIsFocusable);
    p->setFocus();
    myBody.emplace_back(p);
}
