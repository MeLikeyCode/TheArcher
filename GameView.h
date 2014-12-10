#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QKeyEvent>
#include "Player.h"
#include "Bandit.h"
#include "Score.h"
#include <QMediaPlayer>

/**
@mainpage The Archer
@author Abdullah Aghazadah
@version 1.0
@brief The Archer is a C++ Qt powered top down shooting game developed for DeSalvo's PIC 10C class at ucla.

@section Controls Summary
-move with the WASD keys \n
-right click an item to map THAT item to be used whenever you click the right mouse button \n
-left click an item to map THAT item to be used whenever you click the left mouse button \n
-middle click an item to map THAT item to be used whenever you click on the middle mouse button \n
-ESC or Alt + F4 to exit

@section Gameplay Summary
You start out in the middle of map with some initial items on the ground. Simply touch the items to pick them up.
Once an item is picked up clicking on that item with a certain mouse button on the invintory will map THAT item to THAT
mouse button. For example if you pick up a single arrow item, then you left click it on the invintory, now left clicking on
enemies will "use" the single arrow item (which just spawns a single arrow heading towards the location you clicked). The goal
is to continuesly kill as many bandits as possible...until you ineveitably die :P
*/

/**
 *@class GameView
 *@brief The GameView class represents an instance of the entire gamee.
 *
 * The GameView class is the biggest class in the project, it is responsible for handling the overall
 * game logic and allowing each of it's parts to communicate with one another. The GameView class is VERY
 * public, thus all objects can access all of it's attributes. The GameView class handles all inputs (keyboard,
 * mouse, etc...), and general tasks such as adding new bandits, placing walls, etc...
 */

class GameView;
extern GameView * game;

class GameView: public QGraphicsView{
    Q_OBJECT
public:
    // member functions
    GameView(QWidget * parent=0);
    /**
     * @brief Rotates the player towards the mouse position
     * @param event is the QMouseEvent object that describes the position to rotate towards
     */
    void mouseMoveEvent(QMouseEvent *event);
    /**
     * @brief maps an item to a mouse key OR if an item is already mapped, uses that item
     * @param event is the QMouseEvent that describes the mouse button pressed
     */
    void mousePressEvent(QMouseEvent *event);
    /**
     * @brief ignores the double click (causes focus to shift from player to double clicked item, causing trouble)
     * @param event describes the position that was double clicked
     */
    void mouseDoubleClickEvent(QMouseEvent *event);
    /**
     * @brief resizs the scene to make it the same size as the window
     * @param event is the new window size (to which the scene must be set to)
     */
    void resizeEvent(QResizeEvent *event);
    /**
     * @brief moves the player when WASD pressed, exits when ESC pressed
     * @param event describes the key that was pressed
     */
    void keyPressEvent(QKeyEvent * event);
    /**
     * @brief adds a bandit at the specified x and y location
     * @param x is the x pos
     * @param y is the y pos
     */
    void addbandit(int x, int y); //TODO change to addBandit(Bandit * bandit, int x, int y)
    /**
     * @brief adds a bandit at a random location on the top of the screen
     */
    void addBanditAtrandomTop();
    /**
     * @brief adds a bandit at a random location on the bottom of the screen
     */
    void addBanditAtrandomBottom();
    /**
     * @brief adds a bandit at a random location on the right of the screen
     */
    void addBanditAtrandomRight();
    /**
     * @brief adds a bandit at a random location on the left of the screen
     */
    void addBanditAtrandomLeft();
    /**
     * @brief get what round it currently is
     * @return the current round number
     */
    int getRound();
    /**
     * @brief starts the next round (spawning an appropriate number of bandits)
     */
    void nextRound();
    /**
     * @brief returns the number bandits currently in the game
     * @return the number of bandits currently in the game
     */
    int getNumBandits();
    /**
     * @brief sets the number of bandits
     * @param i is the value to set it to
     */
    void setNumBandits(int i);
    /**
     * @brief places walls at random locations on the scene
     */
    void placeWalls();
    /**
     * @brief places a wall at a certain location and with certain properties
     * @param x is the x pos
     * @param y is the y pos
     * @param width is the width you want the wall
     * @param length is the length you want the wall
     * @param rotation is the rotation you want the wall to have
     */
    void placeWall(int x, int y, int width, int length, int rotation);
    /**
     * @brief places a certain item at a certain location
     * @param item is the item to place
     * @param x is the x pos
     * @param y is the y pos
     */
    void placeItem(Item *item, int x, int y);

    // attributes (public because these need to be accessed by pretty much every other class)
    QGraphicsScene * scene;
    Player * player;
    Score * score;
    QList<Bandit *> bandits; // TODO check if this is actually used, can use it to speed up collision detection
    QMediaPlayer * music;
    int round;
    int num_bandits;
    int fps;

public slots:
    void replayMusic(QMediaPlayer::State s);


};

#endif // GAMEVIEW_H
