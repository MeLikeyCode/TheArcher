#ifndef ITEMSINGLEARROW_H
#define ITEMSINGLEARROW_H

#include "Item.h"

/**
 * @class ItemSingleArrow
 * @brief The ItemSingleArrow class represnets a single arrow that is launched upon the item's use.
 */

class ItemSingleArrow: public Item{
public:
    ItemSingleArrow(int ct);
    /**
     * @brief uses the item
     */
    void use();
};

#endif // ITEMSINGLEARROW_H
