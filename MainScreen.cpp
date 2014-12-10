#include "MainScreen.h"
#include "GameView.h"

#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MainScreen::MainScreen(QWidget *parent){
    QLabel * title = new QLabel("<font size=20 color=green>The Archer</font>",this);
    QLabel * how_to = new QLabel(this);
    QPushButton * play_btn = new QPushButton("Play",this);

    QString how_to_txt(QString("-move with the W, A, S and D keys<br>") +
                       QString("-run into items to pick them up<br>") +
                       QString("-left click an item to map THAT item to the LEFT click<br>") +
                       QString("-right click an item to map THAT item to the RIGHT click<br>") +
                       QString("-middle click an item to map THAT item to the MIDDLE click<br>") +
                       QString("-press ESC key or alt+f4 to exit<br>") +
                       QString("*turn up your volume (there is music!)")
                       );

    how_to->setText(how_to_txt);
    how_to->setAlignment(Qt::AlignHCenter);
    title->setAlignment(Qt::AlignHCenter);

    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(how_to);
    layout->addWidget(play_btn);

    setLayout(layout);

    connect(play_btn,SIGNAL(clicked()),this,SLOT(play()));
}

void MainScreen::play(){
    game = new GameView();
    game->showFullScreen(); // show full screen first because placeWalls and addBandit does their thing
                            // depending on the screen width/height
    //game->setFixedSize(1280,720);

    game->placeWalls();
    game->addBanditAtrandomRight();

    //close window
    close();
}
