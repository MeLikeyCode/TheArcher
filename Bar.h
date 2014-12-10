#ifndef BAR_H
#define BAR_H

#include <QGraphicsRectItem>

/**
 * @class Bar
 * @brief The Bar class represents any sort of GUI bar such as health, mana, hunger, etc...
 *
 * The Bar class is a QGraphicsRectItem that will be partially filled based on its current value
 * and it's max value.
 */

class Bar: public QGraphicsRectItem{
public:
    Bar(QGraphicsItem * parent=0);
    /**
     * @brief redraws the bar to reflect it's current value
     */
    void updateBar();
    /**
     * @brief returns the current value of the bar
     * @return the current value of the bar
     */
    int getCurrentVal();
    /**
     * @brief sets the current value of the bar
     * @param v is the value to set it to
     */
    void setCurrentVal(int v);
    /**
     * @brief sets the max value of the bar
     * @param v is the value to set it to
     */
    void setMaxVal(int v);
    /**
     * @brief increments the bar by a certain amount (increases current value)
     * @param amount is the amount to increase the current value by
     */
    void increment(int amount);
    /**
     * @brief decrements the bar by a certain amuont (decreases current value)
     * @param amount is the amount to decrease by
     */
    void decrement(int amount);
private:
    int max_val;
    int current_val;

};

#endif // BAR_H
