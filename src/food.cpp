#include "food.h"
#include <math.h>
#include <QString>
//floor(32 * (rand()%20)) , floor(32 * (rand()%20))
Food::Food(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem(parent)
{
    //setRect(0,0,32,32);
    vector<QString> images = {"://images/Cereja.png", "://images/Cookie.png", "://images/FrutaVerde.png", "://images/FrutaVermelha.png", "://images/FrutaAmarela.png"};
    setPixmap(
        QPixmap(
            images.at(
                floor(
                    rand() % (images.size())))));
    setPos(floor(32 * (rand() % 17)) + 32 * 2, 32 * 2 + floor(32 * (rand() % 17)));
}
