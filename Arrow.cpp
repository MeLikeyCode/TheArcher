#include "Arrow.h"
#include <QTimer>
#include <QList>
#include "Bandit.h"
#include "GameView.h"
#include <qmath.h>
#include "ShootBandit.h"
#include "Wall.h"

Arrow::Arrow(QGraphicsItem *o): QObject(),QGraphicsPixmapItem(){
    // sets the Pixmap
    setPixmap(QPixmap(":/images/arrow.png"));

    // set damage/range
    distance_traveled = 0;
    range = 650;
    damage = 1;

    // set owner
    owner = o;

    // connect a timer to move()
    int MOVE_EVERY = 1000/game->fps;
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(MOVE_EVERY);

}

void Arrow::move(){
    // moves the arrow forward at its current angle. If the arrow goes out of bounds,
    // deletes it. If the arrow collides with a damageable StaticGameObject, call that object's
    // decreaseHealth() method

    int STEP_SIZE = 45;

    // find the dx and dy
    int dx = STEP_SIZE * qCos(qDegreesToRadians(rotation()));
    int dy = STEP_SIZE * qSin(qDegreesToRadians(rotation()));

    setX(x()+dx);
    setY(y()+dy);

    distance_traveled += STEP_SIZE;

    // delete the arrow if its past its range
    if (distance_traveled > range){
        game->scene->removeItem(this);
        delete this;
        return;
    }

    // delete the arrow if its out of bounds
    double pos_x = scenePos().x();
    double pos_y = scenePos().y();
    double scene_width = game->scene->sceneRect().width();
    double scene_height = game->scene->sceneRect().height();
    if (pos_x > scene_width || pos_x < 0 || pos_y > scene_height || pos_y < 0){
        game->scene->removeItem(this);
        delete this;
        return;
    }


    // if the arrow collides with a damageable StaticGameObject, call that objects decreaseHealth(arrow_attack) function
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (size_t i = 0,n = colliding_items.size(); i < n; ++i){
        // if the arrow collides with a wall, delete it
        if (dynamic_cast<Wall *>(colliding_items[i])){
            game->scene->removeItem(this);
            delete this;
            return;
        }

        // if arrow collides with a damageable StaticGameObject that is not its owner
        StaticGameObject * attacked_object = dynamic_cast<StaticGameObject *>(colliding_items[i]);
        if (attacked_object != nullptr && attacked_object->isdamageable() && attacked_object != owner) {
            // subtract health
            attacked_object->decreaseHealth(damage);
            // remove/delete arrow
            game->scene->removeItem(this);
            delete this;
            break;
        }

        // arrow collides with player but player does not own it? damage player!
        if (typeid(*colliding_items[i]) == typeid(Player) && colliding_items[i] != owner) {
            // subtract player health
            Player * p = static_cast<Player *>(colliding_items[i]);
            p->decreaseHealth(damage);
            // remove/delete arrow
            game->scene->removeItem(this);
            delete this;
            break;
        }
    }

}

void Arrow::setOwner(QGraphicsItem *item){
    owner = item;
}

QGraphicsItem *Arrow::getOwner(){
    return owner;
}

int Arrow::getDamage(){
return damage;
}

void Arrow::setDamage(int val){
    damage = val;
}

void Arrow::setRange(int n){
    range = n;
}
