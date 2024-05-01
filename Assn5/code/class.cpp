#include "class.h"
#include <random>
#include <QFile>
#include <QTextStream>

Block::Block(int num)
{
    value = num;
    x=0;
    y=0;
}

Board::Board(QTextStream &stream)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> R(0, 9);
    std::uniform_int_distribution<int> Bnum(0, 3);
    int x1, y1,x2,y2;

    // Initialize all blocks with a value of 0
    for(int i=0; i<4 ; i++){
        for(int j=0; j<4; j++){
            blocks[i][j] = new Block(0);
            blocks[i][j]->x=j;
            blocks[i][j]->y=i;
        }
    }

    // Place two random blocks with a value of 2
    x1=Bnum(rd);
    y1=Bnum(rd);
    do {
        x2=Bnum(rd);
        y2=Bnum(rd);
    }while(x1==x2&&y1==y2);
    blocks[x1][y1]->value = 2;
    blocks[x2][y2]->value = 2;

    // Output the initial placement of the blocks
    if(x1==x2){
        if(y1<y2){
            stream << "INITIAL " << x1+1 << " " << y1+1 << " " << x2+1 << " " << y2+1 << "\n";
        }
        else{
            stream << "INITIAL " << x2+1 << " " << y2+1 << " " << x1 +1<< " " << y1 +1<< "\n";
        }
    }
    else if(x1<x2){
        stream << "INITIAL " << x1+1 << " " << y1 +1<< " " << x2+1 << " " << y2 +1<< "\n";
    }
    else{
        stream << "INITIAL " << x2 +1<< " " << y2 +1<< " " << x1 +1<< " " << y1+1 << "\n";
    }
}

Board::Board()
{
    // Initialize all blocks with a value of 0
    for(int i=0; i<4 ; i++){
        for(int j=0; j<4; j++){
            blocks[i][j] = new Block(0);
            blocks[i][j]->x=j;
            blocks[i][j]->y=i;
        }
    }
}

int Board::merge(Block* A, Block* B, Block* C, Block* D, QString &output){
    Block* block[4];
    block[0] = A;
    block[1] = B;
    block[2] = C;
    block[3] = D;
    int i=0, point=0, rec=0;
    int record[4];

    // Merge blocks by sliding and combining them
    for(i=0;i<4;i++){
        if(block[i]->value!=0){
            record[rec] = block[i]->value;
            block[i]->value=0;
            rec++;
        }
    }
    for(i=0;i<4;i++){
        if(rec>0){
            block[i]->value=record[i];
            rec--;
        }else{
            block[i]->value=0;
        }
    }

    i=0;

    while(i<3){
        if(block[i]->value==block[i+1]->value){
            block[i]->value*=2;
            point+=block[i]->value;
            if(block[i]->value!=0){
                if(output==nullptr){
                    output = "MERGE";
                }
                output += " " +QString::number(block[i]->y+1) + " " + QString::number(block[i]->x+1) + " " + QString::number(block[i]->value);
            }
            for(int j=i+1; j<4;j++){
                if(j==3){
                    block[j]->value = 0;
                    break;
                }
                block[j]->value = block[j+1]->value;
            }
            i++;
        }
        else{
            i++;
        }
    }
    return point;
}

int Board::press_left(QTextStream &stream)
{
    QString output;
    int point=0;
    for(int i=0;i<4;i++){
        point+=merge(blocks[i][0],blocks[i][1],blocks[i][2],blocks[i][3], output);
    }
    if(output!=nullptr){
        stream << output << '\n';
    }
    return point;
}

int Board::press_right(QTextStream &stream)
{
    QString output;
    int point=0;
    for(int i=0;i<4;i++){
        point+=merge(blocks[i][3],blocks[i][2],blocks[i][1],blocks[i][0],output);
    }
    if(output!=nullptr){
        stream << output << '\n';
    }
    return point;
}

int Board::press_up(QTextStream &stream)
{
    QString output;
    int point=0;
    for(int i=0;i<4;i++){
        point+=merge(blocks[0][i],blocks[1][i],blocks[2][i],blocks[3][i],output);
    }
    if(output!=nullptr){
        stream << output << '\n';
    }
    return point;
}

int Board::press_down(QTextStream &stream)
{
    QString output;
    int point=0;
    for(int i=0;i<4;i++){
        point+=merge(blocks[3][i],blocks[2][i],blocks[1][i],blocks[0][i],output);
    }
    if(output!=nullptr){
        stream << output << '\n';
    }
    return point;
}

Game::Game(QTextStream &stream)
{
    gameBoard = new Board(stream);
    preBoard = new Board();
    updateCount();
    score=0;
}

bool Game::findBlock(int target)
{
    for(int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if(gameBoard->blocks[i][j]->value==target){
                return true;
            }
        }
    }
    return false;
}

void Game::newBlock(QTextStream &stream)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> R(0, 9);
    std::uniform_int_distribution<int> Bnum(0, 3);
    int x, y;

    // Find an empty block to place a new block
    while(1){
        x=Bnum(rd);
        y=Bnum(rd);
        if(gameBoard->blocks[y][x]->value==0)
            break;
    }

    // Randomly choose between placing a block with value 2 or 4
    if(R(rd)<2){
        gameBoard->blocks[y][x]->value=4;
        stream << "GENERATE" << " "<<y+1 << " " << x+1 << " "<<4 <<'\n';
    }else{
        gameBoard->blocks[y][x]->value=2;
        stream << "GENERATE" << " "<<y+1 << " " << x+1 << " "<<2 <<'\n';
    }
}

void Game::updateCount()
{
    int num=0;

    // Count the number of non-empty blocks on the board
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(gameBoard->blocks[i][j]->value>0){
                num++;
            }
        }
    }

    block_num=num;
}
