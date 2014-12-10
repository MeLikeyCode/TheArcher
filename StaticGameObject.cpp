#include "StaticGameObject.h"
#include "GameView.h"

extern GameView * game;

StaticGameObject::StaticGameObject(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

}

int StaticGameObject::getHealth(){
    return health;
}

int StaticGameObject::getzheight(){
    return zheight;
}

void StaticGameObject::setHealth(int h){
    health = h;
}

void StaticGameObject::setzheight(int height){
    zheight = height;
}

void StaticGameObject::decreaseHealth(int amount){
    health = health - amount;

    // remove/delete item if health <= 0
    if (health <= 0){
        game->scene->removeItem(this);
        delete this;
    }
}

bool StaticGameObject::isdamageable(){
    return damageable;
}

void StaticGameObject::setdamageable(bool b){
    damageable = b;
}

QPointF StaticGameObject::getOrigin(){
    return mapToScene(transformOriginPoint());
}
