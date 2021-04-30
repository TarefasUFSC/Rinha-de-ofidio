

#include "bodypart.h"
#include <math.h>
BodyPart::BodyPart(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem(parent)
{
}
bool BodyPart::move(string decisao)
{

    if (decisao == "Left")
    {
        // limite para não sair da tela
        if (pos().x() - 32 > 32)
            setPos(32 * floor((x() - 32) / 32), y());
        else
        {
            return false;
        }
    }
    if (decisao == "Right")
    {
        // limite para não sair da tela
        if (pos().x() + 32 < (704 - 32))
            setPos(32 * floor((x() + 32) / 32), y());
        else
        {
            return false;
        }
    }
    if (decisao == "Up")
    {
        if (pos().y() - 32 > 32)
            setPos(x(), 32 * floor((y() - 32) / 32));
        else
        {
            return false;
        }
    }
    if (decisao == "Down")
    {
        if (pos().y() + 32 < (704 - 32))
            setPos(x(), 32 * floor((y() + 32) / 32));
        else
        {
            return false;
        }
    }

    return true;
}
