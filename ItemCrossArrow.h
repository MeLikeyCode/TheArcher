#ifndef ITEMCROSSARROW_H
#define ITEMCROSSARROW_H

#include "Item.h"

/**
 * @class ItemCrossArrow
 * @brief The ItemCrossArrow class represents an item that upon it's use, will fire a bunch of arrows
 * all around the player.
 */

class ItemCrossArrow: public Item{
public:
    ItemCrossArrow(int ct);
    /**
     * @brief uses the item
     */
    void use();
};

#endif // ITEMCROSSARROW_H
