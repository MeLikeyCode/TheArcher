#ifndef INV_H
#define INV_H

#include <QList>
#include "Item.h"
#include <QGraphicsRectItem>

/**
 * @class Inv
 * @brief The Inv class represents a GUI for items the player has collected
 *
 * The Inv class handles both the internal database of items the player has and also displaying them.
 */

class Inv: public QGraphicsRectItem{
public:
    //member functions
    Inv();
    /**
     * @brief redraws the inv to reflect it's current parameters (number of items, item counts, etc...)
     */
    void updateInv();
    /**
     * @brief adds a certain item to the invintory
     * @param item is the item to add
     */
    void addItem(Item *item);
    /**
     * @brief shifts all the items in the invintory 50 pixels to the left (prevents a bug)
     */
    void shiftLeft();

    //attributes
    Item * left_click_item;
    Item * right_click_item;
    Item * middle_click_item;
    QList<Item *> items;
};

#endif // INV_H
