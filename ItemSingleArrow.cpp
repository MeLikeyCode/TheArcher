#include "ItemSingleArrow.h"
#include "Arrow.h"
#include <QDebug>
#include <QImage>
#include <QBrush>
#include "Item.h"
#include "GameView.h"


ItemSingleArrow::ItemSingleArrow(int ct): Item(ct){
    //set the pixmap and scale it
    QPixmap pm(":/images/arrow.png");
    pm = pm.scaled(50,50);
    setPixmap(pm);

    //set the count text
    QPointF pt(mapToScene(0,0));
    count_text->setPos(pt);
}

void ItemSingleArrow::use(){
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

    //create an arrow
    Arrow * arr = new Arrow(game->player);

    //set it's pos and rotation
    arr->setPos(game->player->getOrigin());
    arr->setRotation(game->player->getAngle());

    game->scene->addItem(arr);

    count -=1;
    game->player->inv->updateInv();
}
