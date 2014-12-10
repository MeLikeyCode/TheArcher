#include "GameView.h"
#include <QLineF>
#include <QPointF>
#include <QCursor>
#include <QMediaPlayer>
#include "Wall.h"
#include "Item.h"
#include <QImage>
#include "Inv.h"
#include "ItemSingleArrow.h"
#include "ItemTrippleArrow.h"
#include "ItemCrossArrow.h"
#include <stdlib.h>
#include "ShootBandit.h"
#include "Score.h"
#include "ColliderRight.h"
#include "ColliderLeft.h"
#include "ColliderTop.h"
#include "ColliderBottom.h"

GameView::GameView(QWidget *parent): QGraphicsView(parent){
    // set the frames pers second
    fps = 30;

    // play music
    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/sounds/bg_music.mp3"));
    music->play();
    connect(music,SIGNAL(stateChanged(QMediaPlayer::State)),SLOT(replayMusic(QMediaPlayer::State)));

    // add scene
    scene = new QGraphicsScene(this);

    // add player
    player = new Player(QPixmap(":/images/player.png"));
    player->setFlag(QGraphicsItem::ItemIsFocusable,true);
    player->setFocus();
    player->setPos(300,200);

    // add player's inv to the scene
    player->inv = new Inv();
    scene->addItem(player->inv);

    // add score
    score = new Score();
    score->setPos(300,0);
    scene->addItem(score);

    // set scene background
    scene->setSceneRect(0,0,width(),height());
    QImage * img = new QImage(":/images/grass.png");
    QBrush bg_brush(*img);
    scene->setBackgroundBrush(bg_brush);

    // disable scene item indexing (only useful if you have lots of STATIC graphic items,
    // this game has dynamic graphic items)
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    // add player to scene
    scene->addItem(player);

    // allow the view to recieve mouse move events
    setMouseTracking(true);

    // set the scene and the part of the scene to view (the whole thing in this case)
    setScene(scene);
    setSceneRect(scene->sceneRect());

    // disable scrollbars for the view
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // make window at least 1000x800 and name the window
    setMinimumSize(1000,800);
    setWindowTitle("Village Defense");

    // set the round to 0 initially
    round = 0;

    // set the cursor
    setCursor(QCursor(Qt::CrossCursor));

    // set the number of bandits to 0 initially, then add bandits from the
    // right edge (adding bandits increments num_bandits)
    num_bandits = 0;

    // make a test few items
    ItemSingleArrow * item = new ItemSingleArrow(20);
    placeItem(item,400,400);

    ItemSingleArrow * item2 = new ItemSingleArrow(30);
    placeItem(item2,500,500);

    ItemTrippleArrow * item3 = new ItemTrippleArrow(30);
    placeItem(item3,600,600);

    ItemCrossArrow * item4 = new ItemCrossArrow(30);
    placeItem(item4,700,700);

}

void GameView::mouseMoveEvent(QMouseEvent *event){
    //rotate the player an angle between the player's position and the mouse position
    QPointF pt1(player->getOrigin());
    QPointF pt2(event->pos());
    QLineF line(pt1,pt2);
    double angle = -1 * line.angle();

    // angle of a line is measured COUNTER clock wise
    // rotation of scene items are measured CLOCK wise, therefore we must negate the line angle
    player->setRotation(angle);
    player->setAngle(angle); // player's angle property is used to determine rotation of spawned arrows
}

void GameView::mousePressEvent(QMouseEvent *event){
    // =if the left button was clicked=
    if (event->button() == Qt::LeftButton){
        // if the invintory was clicked, let the invintory handle it
        if (player->inv->contains(event->pos())){
            // the default view mouse press event will propogate the event
            // to the lowest child, in this case it will be the item in the
            // invintory that is clicked, that item will then respond to the
            // mouse press event by mapping itself to the left click event
            QGraphicsView::mousePressEvent(event);
            return;
        }

        // if there is nothing mapped to this click, return (do nothing)
        if (player->inv->left_click_item == nullptr){
            return;
        }

        // other wise, (if some item is mapped to left click) use the item
        player->inv->left_click_item->use();
    }

    // =if the right button was clicked=
    if (event->button() == Qt::RightButton){
        // if the invintory was clicked, let the invintory handle it
        if (player->inv->contains(event->pos())){
            // the default view mouse press event will propogate the event
            // to the lowest child, in this case it will be the item in the
            // invintory that is clicked, that item will then respond to the
            // mouse press event by mapping itself to the left click event
            QGraphicsView::mousePressEvent(event);
            return;
        }

        // if there is nothing mapped to this click, return (do nothing)
        if (player->inv->right_click_item == nullptr){
            return;
        }

        // other wise, (if some item is mapped to this click) use the item
        player->inv->right_click_item->use();

    }

    // =if the mid button was clicked=
    if (event->button() == Qt::MiddleButton){
        // if the invintory was clicked, let the invintory handle it
        if (player->inv->contains(event->pos())){
            // the default view mouse press event will propogate the event
            // to the lowest child, in this case it will be the item in the
            // invintory that is clicked, that item will then respond to the
            // mouse press event by mapping itself to the left click event
            QGraphicsView::mousePressEvent(event);
            return;
        }

        // if there is nothing mapped to this click, return (do nothing)
        if (player->inv->middle_click_item == nullptr){
            return;
        }

        // other wise, (if some item is mapped to left click) use the item
        player->inv->middle_click_item->use();
    }
}

void GameView::mouseDoubleClickEvent(QMouseEvent *event){
    // prevents autofocusing keyboard on QGraphicItem that was double clicked (default behavior of scene)
}

void GameView::resizeEvent(QResizeEvent *event){
    //resize the scene rect, set the view's scene rect to this new scene rect
    scene->setSceneRect(0,0,width(),height());
    setSceneRect(scene->sceneRect());
}

void GameView::keyPressEvent(QKeyEvent *event){
    // if esc is pressed, close the game
    if (event->key() == Qt::Key_Escape)
    close();

    // other wise, pass keyboard event to scene which passes it to focused item (which is the player)
    QGraphicsView::keyPressEvent(event);
}

void GameView::addBanditAtrandomRight(){
    // adds a bandit at a random location on the right edge of the map
    int rand_x_pos = width() + (rand() % 800); //up to 800 pixels horizontally offscreen
    int rand_y_pos = rand() % (height()+200); //up to 200 pixels vertically offscreen

    addbandit(rand_x_pos,rand_y_pos);
}

void GameView::addBanditAtrandomLeft(){
    // adds a bandit at a random location on the left edge of the map
    int rand_x_pos = -1 * (rand() % 800); //up to 800 pixels horizontally offscreen
    int rand_y_pos = rand() % (height()+200); //up to 200 pixels vertically offscreen

    addbandit(rand_x_pos,rand_y_pos);
}

void GameView::addBanditAtrandomTop(){
    // adds a bandit at a random location on the top edge of the map
    int rand_x_pos = rand() % (width()+200); //up to 200 pixels horizontally offscreen
    int rand_y_pos = -1* (rand() % 800); //up to 800 pixels vertically offscreen

    addbandit(rand_x_pos,rand_y_pos);
}

void GameView::addBanditAtrandomBottom(){
    // adds a bandit at a random location on the right edge of the map
    int rand_x_pos = rand() % (width()+200); //up to 200 pixels horizontally offscreen
    int rand_y_pos = rand() % (height()+800); //up to 200 pixels vertically offscreen

    addbandit(rand_x_pos,rand_y_pos);
}

void GameView::addbandit(int x, int y){
    // adds a bandit at the specified location
    int rand_num = rand() % 2; // 0 or 1

    if (rand_num == 0){
        Bandit * bandit = new Bandit();
        bandit->setPos(x,y);
        bandit->setHealth(1+getRound()/3);
        num_bandits++;
        scene->addItem(bandit);
    }
    else {
        ShootBandit * bandit = new ShootBandit();
        bandit->setPos(x,y);
        bandit->setHealth(1+getRound()/3);
        num_bandits++;
        scene->addItem(bandit);
    }
}

int GameView::getRound(){
    return round;
}

void GameView::nextRound(){
    // based on the round number, spawns a number of bandits randomly off screen from all edges
    round++;
    int rand_dir;
    for (size_t i = 0; i <= 1 + round/2; i++){
        rand_dir = rand() % 4; // 0 - 3
        switch (rand_dir){
        case 0:
            addBanditAtrandomTop();
        case 1:
            addBanditAtrandomBottom();
        case 2:
            addBanditAtrandomRight();
        case 3:
            addBanditAtrandomLeft();
        }

    }
}

int GameView::getNumBandits(){
    return num_bandits;
}

void GameView::setNumBandits(int i){
    num_bandits = i;

    if (num_bandits <= 0){
        nextRound();
    }
}

void GameView::placeWalls(){
    // randomly places a bunch of walls on the scene
    int MIN_NUM_WALLS = 3;
    int MAX_NUM_WALLS = 8;

    int num_walls = MIN_NUM_WALLS + ( rand() % ( MAX_NUM_WALLS - MIN_NUM_WALLS + 1 ) );;
    for (size_t i = 0; i < num_walls; ++i){
        int rand_x = rand() % width();
        int rand_y = rand() % height();
        int rand_mult = rand() % 5 + 1; //1-5 times a default size

        int w_or_h = rand() % 2; // 0 or 1
        if (w_or_h == 0){
            placeWall(rand_x,rand_y,64 * rand_mult,64,0);
        }
        else {
            placeWall(rand_x,rand_y,64,64 * rand_mult,0);
        }

    }
}

void GameView::placeWall(int x, int y, int width, int length, int rotation){
    // places a wall at the specified location with the specified properties
    Wall * wall = new Wall();
    wall->setPos(x,y);

    wall->setRect(0,0,width,length);
    wall->setRotation(rotation);

    // add right collider
    ColliderLeft * left = new ColliderLeft(wall);
    left->setRect(0,0,10,wall->rect().height());

    // add right collider
    ColliderRight * right = new ColliderRight(wall);
    right->setRect(0+wall->rect().width()-10,0,10,wall->rect().height());

    // add top collider
    ColliderTop * top = new ColliderTop(wall);
    top->setRect(0,0,wall->rect().width(),10);

    // add bottom collider
    ColliderBottom * bottom = new ColliderBottom(wall);
    bottom->setRect(0,0+wall->rect().height()-10,wall->rect().width(),10);

    scene->addItem(wall);
}

void GameView::placeItem(Item * item, int x, int y){
    // places the item at the specified location on the scene
    item->setPos(x,y);
    scene->addItem(item);
}

void GameView::replayMusic(QMediaPlayer::State s){
    if (s == QMediaPlayer::StoppedState){
        music->play();
    }
}
