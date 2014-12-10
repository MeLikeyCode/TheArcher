#include "Item.h"
#include <QPixmap>
#include "GameView.h"
#include <QBrush>
#include <QRect>
#include <QDebug>
#include <QFont>

Item::Item(int ct){
    // set attributes
    count = ct;
    picked = false;

    //set count text
    count_text = new QGraphicsTextItem(QString::number(count),this);
    count_text->setFont(QFont("Times New Roman",12));
    count_text->setDefaultTextColor(Qt::red);

    //set picture
    //done by derived class's
}

void Item::use(){
    // code that executes when the item is used (use the item and then subtract 1 from count)
    // if the the item count is 0 or less, remove it from player's list

}

int Item::getCount(){
    return count;
}

void Item::setCount(int c){
    count = c;
}

void Item::setAsLeftClickItem(){
     game->player->inv->left_click_item = this;
}

void Item::setAsRightClickItem(){
    game->player->inv->right_click_item = this;
}

void Item::setAsMiddleClickItem(){
    game->player->inv->middle_click_item = this;
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        setAsLeftClickItem();
        game->scene->setFocusItem(game->player);
    }

    if (event->button() == Qt::RightButton){
        setAsRightClickItem();
        game->scene->setFocusItem(game->player);
    }

    if (event->button() == Qt::MiddleButton){
        setAsMiddleClickItem();
        game->scene->setFocusItem(game->player);
    }
}
