#ifndef COLLIDERBOTTOM_H
#define COLLIDERBOTTOM_H

#include <QGraphicsRectItem>
#include <QString>

/**
 * @class ColliderBottom
 * @brief The ColliderBottom class represents a rectangular region, that will cause the player
 * to move back down.
 *
 * If the player collides with a ColliderBottom, we assume the player is coming from the bottom side of
 * the screen, thus we move him back down because Colliders are barriers.
 */

class ColliderBottom: public QGraphicsRectItem{
public:
    ColliderBottom(QGraphicsItem *parent=0);
};

#endif // COLLIDERBOTTOM_H
