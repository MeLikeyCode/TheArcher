#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

/**
 * @class Item
 * @brief The Item class represents any pickable item the player can run into.
 *
 * The Item class is really an abstract class (but not forced to be one). It allows us to work with the
 * concept of pickable items in a general and polymorphic sense. An item MUST be initialized with a count,
 * which describes how many uses the item has.
 */

class Item: public QGraphicsPixmapItem {
public:
    //
    Item(int ct);
    /**
     * @brief uses the item
     */
    virtual void use();
    /**
     * @brief returns the number of uses remaining
     * @return the number of uses remaining
     */
    virtual int getCount();
    /**
     * @brief sets the number of uses
     * @param c is the value to set it to
     */
    virtual void setCount(int c);
    /**
     * @brief maps this item to be used when left mouse button is pressed
     */
    virtual void setAsLeftClickItem();
    /**
     * @brief maps this item to be used when right mouse button is pressed
     */
    virtual void setAsRightClickItem();
    /**
     * @brief maps this item to be used when middle mouse button is pressed
     */
    virtual void setAsMiddleClickItem();
    /**
     * @brief maps the clicked item to the button clicked
     * @param event describes the location that was clicked (thus the inv item clicked)
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

    bool picked;
    QGraphicsTextItem * count_text;
    int count;
    int index;

};

#endif // ITEM_H
