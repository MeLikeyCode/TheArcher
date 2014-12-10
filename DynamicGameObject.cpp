#include "DynamicGameObject.h"
#include <QLineF>
#include <QTimer>
#include "GameView.h"
#include "Wall.h"
#include "ColliderRight.h"
#include "ColliderLeft.h"
#include "ColliderBottom.h"
#include "ColliderTop.h"
#include "qmath.h"

#include <QDebug>
extern GameView * game;

DynamicGameObject::DynamicGameObject(QGraphicsItem *parent): QObject(), StaticGameObject(parent){
    // default speed is 0
    speed = 0;
    can_rotate = true;

    // default pos/destination is 0,0
    x_prev = 0;
    y_prev = 0;
    setPos(0,0);
    destination = QPointF(0,0);

    // connect a timer to step()
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(step()));
    timer->start(1000/game->fps);

    // connect a timer to setCanRotate()
    QTimer * timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(setCanRotate()));
    timer2->start(4000);
}


void DynamicGameObject::setDestination(const QPointF& pt){
    destination = pt;
}

bool DynamicGameObject::shouldBeMoving(){
    // returns true if the object is not near its destination
    QLineF dist(scenePos(),destination);
    int EPS = 5;

    if (dist.length() > EPS) {
        return true;
    }
    else {
        return false;
    }
}

void DynamicGameObject::setSpeed(int s){
    speed = s;
}

bool DynamicGameObject::canRotate(){
    return can_rotate;
}

void DynamicGameObject::step(){
    // moves the object towards its destination if it should be moving TODO make it avoid obsticles
    if (shouldBeMoving()){
        // line between current pos and target
        QLineF ln(scenePos(),destination);
        ln.setLength(speed);

        if (canRotate()){
            setRotation(-1 * ln.angle());
        }

        double dx = ln.dx();
        double dy = ln.dy();
        setPos(x() + dx, y()+ dy);
    }

    // is the DynamicGameObject colliding with anything?
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size();i<n;i++){
        // get angle
        int STEP_SIZE = 15;

        // find the dx and dy
        int dx = STEP_SIZE * qCos(qDegreesToRadians(rotation()));
        int dy = STEP_SIZE * qSin(qDegreesToRadians(rotation()));

        QLineF ln(pos(),QPointF(x()+dx,y()+dy)); // pos of object --- straight in front of it
        double angle = ln.angle();

        // collides w ColliderRight
        if (typeid(ColliderRight) == typeid(*colliding_items[i])){
            setCantRotate();
            if (angle > 180){
                // move down
                setPos(x()+speed,y()+speed);
            }
            else {
                // move up
                setPos(x()+speed,y()-speed);
            }
            return;
        }

        if (typeid(ColliderLeft) == typeid(*colliding_items[i])){
            setCantRotate();
            if (angle > 180){
                // move down
                setPos(x()-speed,y()+speed);
            }
            else {
                // move up
                setPos(x()-speed,y()-speed);
            }
            return;
        }

        if (typeid(ColliderTop) == typeid(*colliding_items[i])){
            setCantRotate();
            if (angle > 90 && angle < 270){
                // move left
                setPos(x()-speed,y()-speed);
            }
            else {
                // move right
                setPos(x()+speed,y()-speed);
            }
            return;
        }

        if (typeid(ColliderBottom) == typeid(*colliding_items[i])){
            setCantRotate();
            if (angle > 90 && angle < 270){
                // move left
                setPos(x()-speed,y()+speed);
            }
            else {
                // move right
                setPos(x()+speed,y()+speed);
            }
            return;
        }
    }

    // other wise, if there is no collisions, set this as his new previous position
    x_prev = pos().x();
    y_prev = pos().y();
}

void DynamicGameObject::setCanRotate(){
    can_rotate = true;
}

void DynamicGameObject::setCantRotate(){
    can_rotate = false;
}
