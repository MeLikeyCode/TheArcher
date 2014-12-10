#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <QGraphicsItem>

/**
@class Arrow
@brief Represents a projectile that moves forward at it's current rotation.

The Arrow class is a QGraphicsPixmapItem which will move forward at it's current rotation
based on it's speed. Every Arrow object has an owner, when an arrow collides with any
damageable StaticGameObject other than the owner, that object's decreaseHealth(amount) function will be
called.
*/

class Arrow: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
        Arrow(QGraphicsItem * o);
public slots:
        /**
         * @brief moves the arrow and handles collisions
         *
         * Every game tick, the arrow is moved forward at it's current angle. After the movement,
         * we check whether it has collided with anything and handle it appropriately. For
         * example if the arrow collides with any damageable StaticGameObject other than it's owner,
         * call that objects decreaseHealth() function. We also check if the arrow is out of bounds
         * so that we can delete it.
         */
        void move();
        /**
         * @brief sets the owner of the arrow
         * @param item is a pointer to the owner
         */
        void setOwner(QGraphicsItem * item);
        /**
         * @brief returns the owner of the arrow
         * @return the owner
         */
        QGraphicsItem * getOwner();
        /**
         * @brief returns the amount of damage the arrow does
         * @return the damage
         */
        int getDamage();
        /**
         * @brief sets the damage of the arrow
         * @param val is the value to set damage to
         */
        void setDamage(int val);
        /**
         * @brief sets the range of the arrow
         * @param n the value to set range to
         */
        void setRange(int n);
private:
        QGraphicsItem * owner;
        int damage;
        int distance_traveled;
        int range;
};

#endif // ARROW_H
