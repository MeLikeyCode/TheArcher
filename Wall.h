#ifndef WALL_H
#define WALL_H

#include <QGraphicsRectItem>

/**
 * @class Wall
 * @brief The Wall class represents a barrier for all DynamicGameObjects.
 *
 * When arrows collide with walls, they get destroyed. When the player collides with walls, he is blocked.
 * When enemies collide with walls, they try to either a)find a way around or b) jump over the wall.
 */

class Wall: public QGraphicsRectItem{
public:
    Wall();
};

#endif // WALL_H
