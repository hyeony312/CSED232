#ifndef GAMEUI_H
#define GAMEUI_H

#include "class.h"
#include "blockui.h"
#include <QtWidgets>
#include <QFile>
#include <QTextStream>

class GameUi : public QWidget
{
    Q_OBJECT
public:
    explicit GameUi(QWidget *parent = nullptr);

    //methods
    void UpdateUI();

protected:
    void keyPressEvent(QKeyEvent *event);
    void PressRestore();
    void PressQuit();
    void emptySlot(){}

private:
    BlockUi *myBlock[4][4];
    Game* myGame;
    QLabel* scoreLabel;
    QPushButton* restoreButton;
    QPushButton* exitButton;

    QFile file;
    QTextStream stream;
signals:

};

#endif // GAMEUI_H
