#include "Player.h"
#include "Wall.h"
#include "GameView.h"
#include "HealthPotion.h"

#include <QDebug>
Player::Player(QPixmap &pixmap): QObject(), QGraphicsPixmapItem(pixmap){
    // make player rotate at another point rather than at 0,0
    setTransformOriginPoint(20,38);

    // initialize previous pos
    x_prev = pos().x();
    y_prev = pos().y();

    // initialize health bar
    health = 20;
    max_health = 20;
    health_bar = new Bar(this);
    health_bar->setMaxVal(20);
    health_bar->setCurrentVal(20);
}

void Player::keyPressEvent(QKeyEvent *event){
    if (
        event->key() == Qt::Key_W ||
        event->key() == Qt::Key_A ||
        event->key() == Qt::Key_S ||
        event->key() == Qt::Key_D
       )
    {
        keysPressed.insert(event->key());
    }

    int STEP_SIZE = 10;

    //if only 1 key is being pressed, simply move in that direction
    if (keysPressed.size() == 1){
        switch (event->key()){
        case Qt::Key_D:
            setPos(x()+STEP_SIZE,y());
            break;
        case Qt::Key_A:
            setPos(x()-STEP_SIZE,y());
            break;
        case Qt::Key_W:
            setPos(x(),y()-STEP_SIZE);
            break;
        case Qt::Key_S:
            setPos(x(),y()+STEP_SIZE);
            break;
        }
    }

    //if two keys are being pressed, move diagonally
    if (keysPressed.size() > 1){

        // up right
        if (keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_D)){
            setPos(x()+STEP_SIZE,y()-STEP_SIZE);
        }
        // up left
        if (keysPressed.contains(Qt::Key_W) && keysPressed.contains(Qt::Key_A)){
            setPos(x()-STEP_SIZE,y()-STEP_SIZE);
        }
        // down right
        if (keysPressed.contains(Qt::Key_S) && keysPressed.contains(Qt::Key_D)){
            setPos(x()+STEP_SIZE,y()+STEP_SIZE);
        }
        // down left
        if (keysPressed.contains(Qt::Key_S) && keysPressed.contains(Qt::Key_A)){
            setPos(x()-STEP_SIZE,y()+STEP_SIZE);
        }
    }

    // is the player colliding with anything?
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size();i<n;i++){
        // player collides w Wall - move him back to his previous position
        if (typeid(Wall) == typeid(*colliding_items[i])){
            setPos(x_prev,y_prev);
            return;
        }
        // player collides w health potion
        else if (typeid(HealthPotion) == typeid(*colliding_items[i])){
            increaseHealth(); // TODO generalize the 1 to some property of the potion (hp)
            game->scene->removeItem(colliding_items[i]);
        }
        // player collides with Item - add the item to player's invintory
        else{
            Item * item = dynamic_cast<Item *>(colliding_items[i]);
                if (item != nullptr && item->picked == false){
                inv->addItem(item);
            }
        }
    }

    // other wise, if there is no collisions, set this as his new previous position
    x_prev = pos().x();
    y_prev = pos().y();

}

void Player::keyReleaseEvent(QKeyEvent *event){
    keysPressed.remove(event->key());
}

void Player::setAngle(double a){
    angle = a;
}

double Player::getAngle() const{
    return angle;
}

QPointF Player::getOrigin(){
    return mapToScene(transformOriginPoint());
}

void Player::decreaseHealth(double amount){
    health = health - amount;
    health_bar->decrement(amount);
    health_bar->updateBar();

    if (health <= 0){
        qDebug() << "Game Over";
        game->close();
    }
}

void Player::increaseHealth(){
    if (health < max_health){
        health = health + 5;
        health_bar->increment(5);
        health_bar->updateBar();
    }
}
