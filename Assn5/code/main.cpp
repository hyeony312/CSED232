#include <QApplication>
#include "gameui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameUi *Game = new GameUi();
    Game->resize(1300, 1000);
    Game->show();

    return a.exec();
}
