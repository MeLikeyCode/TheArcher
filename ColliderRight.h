#ifndef COLLIDERRIGHT_H
#define COLLIDERRIGHT_H

#include <QGraphicsRectItem>
#include <QString>

/**
 * @class ColliderRight
 * @brief The ColliderRight class represents a rectangular region, that will cause the player
 * to move back right.
 *
 * If the player collides with a ColliderRight, we assume the player is coming from the right side of
 * the screen, thus we move him back right because Colliders are barriers.
 */

class ColliderRight: public QGraphicsRectItem{
public:
    ColliderRight(QGraphicsItem *parent=0);
};

#endif // COLLIDERRIGHT_H
