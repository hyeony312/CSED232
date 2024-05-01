#ifndef CLASS_H
#define CLASS_H

#include <QFile>
#include <QTextStream>

class Block
{
public:
    Block(int num=0);
    int value;
    int x;
    int y;
};

class Board
{
public:
    Board(QTextStream &stream);
    Board();
    // methods
    int merge(Block* A, Block* B, Block* C, Block* D, QString &output);
    int press_left(QTextStream &stream);
    int press_right(QTextStream &stream);
    int press_up(QTextStream &stream);
    int press_down(QTextStream &stream);

    // members
    Block* blocks[4][4];
};

class Game
{
public:
    Game(QTextStream &stream);

    void newBlock(QTextStream &stream);
    void updateCount();
    bool findBlock(int target);

    Board* gameBoard;
    Board* preBoard;
    int preScore=0;
    int restoreCount=3;
    int hasBuff=0;

    int score=0;
    int block_num=0;
};

#endif // CLASS_H
