#ifndef ITEMTRIPPLEARROW_H
#define ITEMTRIPPLEARROW_H

#include "Item.h"

/**
 * @class ItemTrippleArrow
 * @brief The ItemTrippleArrow class represents an item that upon it's use will spanw 3 arrows at once.
 */

class ItemTrippleArrow: public Item{
public:
    ItemTrippleArrow(int ct);
    /**
     * @brief uses the item
     */
    void use();
};

#endif // ITEMTRIPPLEARROW_H
