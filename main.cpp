#include <QApplication>
#include "GameView.h"
#include <QDebug>
#include <stdlib.h> // srand and rand
#include <time.h> // time(0)
#include "MainScreen.h"

// make game a global variables, so all class's can access it
GameView * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(0));

    MainScreen main;
    main.setMinimumSize(800,600);
    main.show();

    return a.exec();
}
