#include "Bandit.h"
#include "Wall.h"
#include <qmath.h>
#include <QPointF>
#include <QLineF>
#include <stdlib.h> // srand and rand
#include <time.h> // time(0)
#include <QTimer>
#include "ItemCrossArrow.h"
#include "ItemSingleArrow.h"
#include "ItemTrippleArrow.h"
#include "GameView.h"
#include "HealthPotion.h"

#include <QDebug>
Bandit::Bandit(QGraphicsItem *parent): DynamicGameObject(parent){
    // set graphics
    setPixmap(QPixmap(":/images/bandit.png"));

    // set origin
    setTransformOriginPoint(33,43);

    // initialize health bar/make damageable
    health_bar = new Bar(this);
    health_bar->setCurrentVal(1+ game->getRound()/3);
    health_bar->setMaxVal(1+ game->getRound()/3);
    setdamageable(true);

    // set destination to be always towards player
    setSpeed(5);
    setDestination(game->player->getOrigin());
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(setDestToPlayer()));
    timer->start(1000/game->fps);

    // connect a timer to damage the player if colliding with bandit
    QTimer * timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(damagePlayerIfColliding()));
    timer2->start(1000);
}


void Bandit::decreaseHealth(int amount){
    // decrement health/health bar
    health_bar->decrement(amount);
    setHealth(getHealth()-amount);

    // remove/delete item if health <= 0
    if (getHealth() <= 0){
        //spawn random item
        int rand_int = rand() % 10 + 1; // 1 - 10
        if (rand_int == 1){
            //spawn single arrow item
            ItemSingleArrow * item = new ItemSingleArrow(10);
            game->placeItem(item,x(),y());
        }
        if (rand_int == 2){
            ItemTrippleArrow * item = new ItemTrippleArrow(10);
            game->placeItem(item,x(),y());
        }
        if (rand_int == 3){
            ItemCrossArrow * item = new ItemCrossArrow(10);
            game->placeItem(item,x(),y());
        }

        if (rand_int == 4){
            HealthPotion * potion = new HealthPotion();
            potion->setPos(x(),y());
            game->scene->addItem(potion);
        }

        // delete bandit
        game->scene->removeItem(this);
        game->setNumBandits(game->getNumBandits()-1);
        game->score->increase();
        delete this;
    }
}

void Bandit::setDestToPlayer(){
    if (!collidesWithItem(game->player))
        setDestination(game->player->getOrigin());
}

void Bandit::damagePlayerIfColliding(){
    if (collidesWithItem(game->player)){
        game->player->decreaseHealth(1);
    }
}
