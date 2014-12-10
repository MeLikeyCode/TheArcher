#ifndef COLLIDERLEFT_H
#define COLLIDERLEFT_H

#include <QGraphicsRectItem>
#include <QString>

/**
 * @class ColliderLeft
 * @brief The ColliderLeft class represents a rectangular region, that will cause the player
 * to move back left.
 *
 * If the player collides with a ColliderLeft, we assume the player is coming from the left side of
 * the screen, thus we move him back left because Colliders are barriers.
 */

class ColliderLeft: public QGraphicsRectItem{
public:
    ColliderLeft(QGraphicsItem *parent=0);
};

#endif // COLLIDERLEFT_H
