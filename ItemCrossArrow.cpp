#include "ItemCrossArrow.h"
#include "Arrow.h"
#include <QDebug>
#include <QImage>
#include <QBrush>
#include "Item.h"
#include "GameView.h"


ItemCrossArrow::ItemCrossArrow(int ct): Item(ct){
    //set the pixmap and scale it
    QPixmap pm(":/images/crossarrow.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);

    //set the count text
    QPointF pt(mapToScene(0,0));
    count_text->setPos(pt);
}

void ItemCrossArrow::use(){
    // don't fire if there isn't enough arrows...
    if (count == 0){
        game->player->inv->items.removeAll(this);
        game->player->inv->shiftLeft();
        game->scene->removeItem(this);
        return;
    }
    if (count < 0){
        return;
    }

    for (size_t i = 0; i <= 360; i+=10){
        Arrow * arr = new Arrow(game->player);
        arr->setPos(game->player->x()+32,game->player->y()+32);
        arr->setRotation(game->player->getAngle()+i);
        game->scene->addItem(arr);
    }

    count -=1;
    game->player->inv->updateInv();
}

