#ifndef COLLIDERTOP_H
#define COLLIDERTOP_H

#include <QGraphicsRectItem>
#include <QString>

/**
 * @class ColliderTop
 * @brief The ColliderTop class represents a rectangular region, that will cause the player
 * to move back up.
 *
 * If the player collides with a ColliderTop, we assume the player is coming from the top side of
 * the screen, thus we move him back up because Colliders are barriers.
 */

class ColliderTop: public QGraphicsRectItem{
public:
    ColliderTop(QGraphicsItem *parent=0);
};

#endif // COLLIDERTOP_H
