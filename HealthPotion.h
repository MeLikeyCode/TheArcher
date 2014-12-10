#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

/**
 * @class HealthPotion
 * @brief The HealthPotion class represents an item that heals the player upon collision
 *
 * When the player collides with an instance of this class, the object is destroyed, and the player's
 * health is increased.
 */

class HealthPotion: public QGraphicsPixmapItem{
public:
    HealthPotion(QGraphicsItem * parent=0);
private:
};

#endif // HEALTHPOTION_H
