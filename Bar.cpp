#include "Bar.h"
#include <QBrush>

Bar::Bar(QGraphicsItem *parent): QGraphicsRectItem(parent){
    // set initial values and draw initial bar
    max_val = 1;
    current_val = 1;

    setRect(parent->pos().x(),parent->pos().y(),80,5);
    setBrush(QBrush(Qt::red));
    setRotation(90);

}

void Bar::updateBar(){
    // updates the bar graphics to the current amount of fullness
    double fill_fraction = double(current_val) / max_val;
    setRect(rect().x(),rect().y(),fill_fraction * 80,5);
}

int Bar::getCurrentVal(){
    return current_val;
}

void Bar::setCurrentVal(int v){
    current_val = v;
}

void Bar::setMaxVal(int v){
    max_val = v;
}

void Bar::increment(int amount){
    // increases the amount the bar is filled (and updates the graphics)
    current_val = current_val + amount;
    updateBar();
}

void Bar::decrement(int amount){
     // decreases the amount the bar is filled (and updates the graphics)
    current_val = current_val - amount;
    updateBar();
}
