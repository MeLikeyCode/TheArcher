#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>
#include "Inv.h"
#include "Bar.h"
#include <QSet>
#include <QPointF>

/**
 * @class Player
 * @brief The Player class represents the player.
 *
 * The player responds to keyboard event (WASD) by moving. Furthermore, responds to mouse events by either
 * mapping a certain item to a click that has not been mapped already, or if the click is already mapped, will
 * simply use the item.
 */

class Player: public QObject, public QGraphicsPixmapItem {
public:
        Player(QPixmap &pixmap);
        /**
         * @brief moves the player if WASD is pressed
         * @param event describes the key pressed
         */
        void keyPressEvent(QKeyEvent * event);
        /**
         * @brief allows for diagonal movement
         * @param event describes the key released
         */
        void keyReleaseEvent(QKeyEvent * event);
        /**
         * @brief sets the angle of the player (used to spawn arrows at correct angle)
         * @param a is the value to set it to
         */
        void setAngle(double a);
        /**
         * @brief returns the current angle of the player
         * @return the current angle of the player
         */
        double getAngle() const;
        /**
         * @brief returns the coordinates around which the player should rotate (in scene coordinates)
         * @return the player's origin (point to rotate around)
         */
        QPointF getOrigin();

        Inv * inv;
        Bar * health_bar;
        QSet<int> keysPressed;
public slots:
        /**
         * @brief decreases the player's health, if 0, game over.
         * @param amount is the amount to decrease the health by
         */
        void decreaseHealth(double amount);
        /**
         * @brief increases the health of the player if it isn't maxed out already
         */
        void increaseHealth();
private:
        double x_prev;
        double y_prev;
        int angle;
        double health;
        double max_health;
};

#endif // PLAYER_H
