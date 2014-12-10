
#include "ItemTrippleArrow.h"
#include "Arrow.h"
#include <QDebug>
#include <QImage>
#include <QBrush>
#include "Item.h"
#include "GameView.h"


ItemTrippleArrow::ItemTrippleArrow(int ct): Item(ct){
    //set the pixmap and scale it
    QPixmap pm(":/images/tripplearrow.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);

    //set the count text
    QPointF pt(mapToScene(0,0));
    count_text->setPos(pt);
}

void ItemTrippleArrow::use(){
    // don't fire if there isn't enough arrows...
    if (count <= 0){
        game->player->inv->items.removeAll(this);
        game->player->inv->shiftLeft();
        game->scene->removeItem(this);
        return;
    }
    if (count < 0){
        return;
    }

    //create three arrow
    Arrow * arr1 = new Arrow(game->player);
    Arrow * arr2 = new Arrow(game->player);
    Arrow * arr3 = new Arrow(game->player);

    //set their pos and rotation
    arr1->setPos(game->player->x()+32,game->player->y()+32); // 32 is player width
    arr2->setPos(game->player->x()+32,game->player->y()+32);
    arr3->setPos(game->player->x()+32,game->player->y()+32);
    arr1->setRotation(game->player->getAngle());
    arr2->setRotation(game->player->getAngle()+10);
    arr3->setRotation(game->player->getAngle()-10);

    game->scene->addItem(arr1);
    game->scene->addItem(arr2);
    game->scene->addItem(arr3);

    count -=1;
    game->player->inv->updateInv();
}
