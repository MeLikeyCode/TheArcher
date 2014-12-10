#ifndef BANDIT_H
#define BANDIT_H

#include "DynamicGameObject.h"
#include <QPixmap>
#include <QObject>
#include "Bar.h"
#include <QGraphicsItem>

/**
 * @class Bandit
 * @brief The Bandit class represents a melee enemy for the player. A Bandit object will move
 * towards the player avoiding obstacles as necessary. When the bandit reaches the player, the
 * player gets damaged. Additionally, when bandits die, there is a chance they drop an pickable item.
 */

class Bandit: public DynamicGameObject {
    Q_OBJECT
public:
    Bandit(QGraphicsItem * parent=0);
    /**
     * @brief decreases the bandit's health by a certain amount
     * @param amount is the amount to decrease the health by
     */
    void decreaseHealth(int amount);
public slots:
    /**
     * @brief sets the bandits current destination to be at the player's location
     */
    void setDestToPlayer();
    /**
     * @brief damages the player when colliding
     */
    void damagePlayerIfColliding();
private:
    Bar *  health_bar;
};

#endif // BANDIT_H
