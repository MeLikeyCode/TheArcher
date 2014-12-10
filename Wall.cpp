#include "Wall.h"
#include <QBrush>
#include <QImage>
#include "ColliderRight.h"
#include "GameView.h"
#include "QLineF"
#include "QPointF"

extern GameView * game;

Wall::Wall(): QGraphicsRectItem(){
    QImage * img = new QImage(":/images/wall.png");
    QBrush brush(*img);
    setBrush(brush);
}
