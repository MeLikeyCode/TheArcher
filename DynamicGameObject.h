#ifndef DYNAMICGAMEOBJECT_H
#define DYNAMICGAMEOBJECT_H

#include "StaticGameObject.h"
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>

/**
 * @class DynamicGameObject
 * @brief The DynamicGameObject class represents any game object that must move.
 *
 * A DynamicGameObject is simply a StaticGameObject that has the capeability of moving. The
 * DynamicGameObject has a destination property that he will move towards (avoiding obsticles).
 * Once at his destination, the object no longer moves.
 */

class DynamicGameObject: public QObject, public StaticGameObject{
    Q_OBJECT
public:
    DynamicGameObject(QGraphicsItem * parent=0);
    /**
     * @brief sets the destination to move towards
     * @param pt is the destination to move towards
     */
    void setDestination(const QPointF& pt);
    /**
     * @brief returns true if the DynamicGameObject should be moving (if not at destination), false other wise
     * @return true if should be moving
     */
    bool shouldBeMoving();
    /**
     * @brief sets the speed to move with
     * @param s is the value to set the speed to
     */
    void setSpeed(int s);
    /**
     * @brief returns true if the DynamicGameObject can rotate right now
     * @return true if the object can rotate
     */
    bool canRotate();
public slots:
    void step();
    void setCanRotate();
    void setCantRotate();
private:
    int speed;
    QPointF destination;
    double x_prev;
    double y_prev;
    bool can_rotate;
};

#endif // DYNAMICGAMEOBJECT_H
