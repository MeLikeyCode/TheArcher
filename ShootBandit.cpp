#include "ShootBandit.h"
#include <QPointF>
#include <QLineF>
#include "GameView.h"
#include "Arrow.h"
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include "Item.h"
#include "ItemSingleArrow.h"
#include "ItemTrippleArrow.h"
#include "ItemCrossArrow.h"
#include "HealthPotion.h"

extern GameView * game;

void ShootBandit::shootAtPlayer(){
    // find angle between bandit and player
    QPointF bandit_pt(getOrigin());
    QPointF player_pt(game->player->getOrigin());
    QLineF ln(bandit_pt,player_pt);
    int ang = -1 * ln.angle();

    // spawn arrow
    Arrow * arr = new Arrow(this);
    arr->setOwner(this);
    arr->setRotation(ang);
    arr->setPos(getOrigin());
    game->scene->addItem(arr);
}

void ShootBandit::setDestToPlayer(){
    // stop within 400 pixels of player
    QLineF ln(game->player->getOrigin(),scenePos());
    ln.setLength(400);
    setDestination(ln.p2());
}

ShootBandit::ShootBandit(QGraphicsItem *parent): DynamicGameObject(parent){
    // set graphics
    setPixmap(QPixmap(":/images/shootbandit.png"));

    // set origin
    setTransformOriginPoint(22,44);

    // initialize health bar
    health_bar = new Bar(this);
    health_bar->setCurrentVal(1+ game->getRound()/3);
    health_bar->setMaxVal(1+ game->getRound()/3);

    // set destination to be always towards player
    setSpeed(5);
    setDestination(game->player->getOrigin());
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(setDestToPlayer()));
    timer->start(1000/game->fps);

    // connect a timer to shootAtPlayer()
    QTimer * shoottimer = new QTimer(this);
    connect(shoottimer,SIGNAL(timeout()),this,SLOT(shootAtPlayer()));
    shoottimer->start(2000);
}


void ShootBandit::decreaseHealth(int amount){
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

        game->scene->removeItem(this);
        game->setNumBandits(game->getNumBandits()-1);
        game->score->increase();
        delete this;
    }


    //check if all bandits are dead, if so go to next round
    if (game->getNumBandits() <= 0){
        game->nextRound();
    }
}
