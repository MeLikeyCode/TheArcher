#ifndef SHOOTBANDIT_H
#define SHOOTBANDIT_H

#include "DynamicGameObject.h"
#include <QPixmap>
#include <QObject>
#include "Bar.h"
#include <QGraphicsItem>

/**
 * @class ShootBandit
 * @brief The ShootBandit class represents a bandit that can attack the player from a range.
 *
 * The ShootBandit object is basically a Bandit object, except it has the capeability of firing
 * arrows at the player. Another difference is that ShootBandits will run AWAY from the player if the
 * player gets TOO close to them, where as Bandit objects always run towards player.
 */

class ShootBandit: public DynamicGameObject {
    Q_OBJECT
public:
    ShootBandit(QGraphicsItem * parent=0);
    /**
     * @brief decreases the health
     * @param amount is the amount to decrease by
     */
    void decreaseHealth(int amount);
public slots:
    /**
     * @brief sets the destination to be towards the player
     */
    void setDestToPlayer();
    /**
     * @brief periodically shoots at the player
     */
    void shootAtPlayer();
private:
    Bar *  health_bar;
};

#endif // SHOOTBANDIT_H
