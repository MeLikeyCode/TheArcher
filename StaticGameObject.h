#ifndef STATICGAMEOBJECT_H
#define STATICGAMEOBJECT_H

#include <QGraphicsPixmapItem>
#include <QPointF>

/**
 * @class StaticGameObject
 * @brief The StaticGameObject class is the base class of all game objects that are static.
 *
 * A StaticGameObject is simply any object that needs properties such as, health, damageable, etc...
 * but do not need to move.
 */

class StaticGameObject: public QGraphicsPixmapItem {
public:
    StaticGameObject(QGraphicsItem * parent=0);
    /**
     * @brief returns the health of the object
     * @return the health
     */
    virtual int getHealth();
    /**
     * @brief returns the zheight of the object
     * @return the zheight
     */
    virtual int getzheight();
    /**
     * @brief sets the health of the object
     * @param h is the value to set it to
     */
    virtual void setHealth(int h);
    /**
     * @brief sets the zheight of the object
     * @param height is the value to set it to
     */
    virtual void setzheight(int height);
    /**
     * @brief decreases the objects health (kill it if < 0)
     * @param amount is the amount to decrease by
     */
    virtual void decreaseHealth(int amount);
    /**
     * @brief Returns true if the object is damageable
     * @return true if damageable
     */
    virtual bool isdamageable();
    /**
     * @brief set the item to be damageable or not damageable
     * @param b is a bool, true -> damgeable, false->not damageable
     */
    virtual void setdamageable(bool b);
    /**
     * @brief returns the origin of the object (point to rotate around)
     * @return the origin
     */
    virtual QPointF getOrigin();
private:
    int health;
    int zheight;
    bool damageable;
};

#endif // STATICGAMEOBJECT_H
