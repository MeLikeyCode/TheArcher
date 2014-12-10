#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

/**
 * @class Score
 * @brief The Score class repersents a GUI that displays the player's current score.
 */

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    /**
     * @brief increases the score
     */
    void increase();
    /**
     * @brief returns the current score
     * @return the current score
     */
    int getScore();
private:
    int score;
};

#endif // SCORE_H
