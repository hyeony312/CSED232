#include <QtWidgets>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include "class.h"
#include "gameui.h"

GameUi::GameUi(QWidget *parent)
    : QWidget{parent}
{
    // Open file
    file.setFileName("progress.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        stream.setDevice(&file);
    }
    else {
        qDebug() << "Failed to open file:" << file.errorString();
    }

    // GUI initialization
    // Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    QGridLayout *boardLayout = new QGridLayout();
    boardLayout->setSpacing(10);

    // Add block labels to the grid layout
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            myBlock[i][j] = new BlockUi(this);
            boardLayout->addWidget(myBlock[i][j], i, j);
        }
    }
    mainLayout->addLayout(boardLayout);

    QVBoxLayout *RightLayout = new QVBoxLayout();
    RightLayout->setSpacing(10);

    // Score display label
    scoreLabel = new QLabel(this);
    scoreLabel->setStyleSheet("QLabel { color: black; }");
    scoreLabel->setText("Score: 0 ");
    scoreLabel->setAlignment(Qt::AlignCenter);
    RightLayout->addWidget(scoreLabel, 0, Qt::AlignTop);

    QFont font1 = scoreLabel->font();
    font1.setPointSize(30);
    scoreLabel->setFont(font1);

    // Restore button
    restoreButton = new QPushButton("Restore", this);
    restoreButton->setFixedSize(300, 200);
    RightLayout->addWidget(restoreButton, 3);

    QFont font3 = restoreButton->font();
    font3.setPointSize(20);
    restoreButton->setFont(font3);

    connect(restoreButton, &QPushButton::clicked, this, &GameUi::PressRestore);

    // Exit button
    exitButton = new QPushButton("Exit", this);
    exitButton->setFixedSize(300, 200);
    RightLayout->addWidget(exitButton, 2);

    QFont font2 = exitButton->font();
    font2.setPointSize(20);
    exitButton->setFont(font2);

    connect(exitButton, &QPushButton::clicked, this, &GameUi::PressQuit); // exit

    // Change focus policy
    restoreButton->setFocusPolicy(Qt::NoFocus);
    exitButton->setFocusPolicy(Qt::NoFocus);

    mainLayout->addLayout(RightLayout);

    // Member initialization
    myGame = new Game(stream);
    stream.flush();
    UpdateUI();
}

void GameUi::PressQuit(){
    // Display quit confirmation dialog
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Exit");
    msgBox.setText("Are you sure you want to quit?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if(msgBox.exec()==QMessageBox::Yes){
        QApplication::quit();
    }
    return;
}

void GameUi::PressRestore()
{
    if(myGame->restoreCount==0){
        // Display message when restore count is 0
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Restore");
        msgBox.setText("No more chances to restore the board to its previous state.");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.exec();
        return;
    }

    // Display restore confirmation dialog
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Restore");
    msgBox.setText("Restore the game board to its previous state?");
    msgBox.setInformativeText("Remaining chances: " + QString::number(myGame->restoreCount));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int result = msgBox.exec();

    if (result == QMessageBox::Yes) {
        if(myGame->hasBuff==1){
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    myGame->gameBoard->blocks[i][j]->value=myGame->preBoard->blocks[i][j]->value;
                }
            }
            myGame->score=myGame->preScore;
            myGame->hasBuff=0;
            myGame->restoreCount--;
            UpdateUI();
            QMessageBox msgBox2;
            msgBox2.setIcon(QMessageBox::Information);
            msgBox2.setWindowTitle("Restore");
            msgBox2.setText("The board has been restored to its previous state!");
            msgBox2.setStandardButtons(QMessageBox::Ok);
            msgBox2.exec();
            stream << "RESTORE " << myGame->restoreCount << '\n';
            stream.flush();
        }
        else{
            QMessageBox msgBox2;
            msgBox2.setIcon(QMessageBox::Information);
            msgBox2.setWindowTitle("Restore");
            msgBox2.setText("There is no previously saved board in the buffer.");
            msgBox2.setStandardButtons(QMessageBox::Ok);
            msgBox2.exec();
        }
    } else {
        // Do nothing if "No" is selected
    }
}

void GameUi::keyPressEvent(QKeyEvent *event)
{
    if(myGame->restoreCount>0){
        // Save current board state before each move if restore count is greater than 0
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                myGame->preBoard->blocks[i][j]->value=myGame->gameBoard->blocks[i][j]->value;
            }
        }
        myGame->hasBuff=1;
        myGame->preScore=myGame->score;
    }

    // Handle key events for game moves
    if(event->key() == Qt::Key_Left)
    {
        stream << "LEFT" <<'\n';
        myGame->score+=myGame->gameBoard->press_left(stream);
    }
    else if(event->key() == Qt::Key_Right)
    {
        stream << "RIGHT"<<'\n';
        myGame->score+=myGame->gameBoard->press_right(stream);
    }
    else if(event->key() == Qt::Key_Up)
    {
        stream << "UP" << '\n';
        myGame->score+=myGame->gameBoard->press_up(stream);
    }
    else if(event->key() == Qt::Key_Down)
    {
        stream << "DOWN" << '\n';
        myGame->score+=myGame->gameBoard->press_down(stream);
    }
    else{
        return;
    }

    UpdateUI();

    if(myGame->findBlock(2048)){
        QTimer::singleShot(1000, this, SLOT(emptySlot()));

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Win");
        msgBox.setInformativeText("Congratulation!");
        msgBox.setText("Score: " + QString::number(myGame->score));
        msgBox.setStandardButtons(QMessageBox::Ok);
        if(msgBox.exec()){
            QApplication::quit();
        }
    }

    myGame->updateCount();

    if(myGame->block_num==16){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Lose");
        msgBox.setInformativeText("You lose...");
        msgBox.setText("Score: " + QString::number(myGame->score));
        msgBox.setStandardButtons(QMessageBox::Ok);
        if(msgBox.exec()){
            QApplication::quit();
        }
    }
    myGame->newBlock(stream);

    UpdateUI();

    stream << "SCORE " << myGame->score << '\n';
    stream.flush();
}

void GameUi::UpdateUI()
{
    int val;
    QString _score="Score: " + QString::number(myGame->score);
    scoreLabel->setText(_score);

    for(int i=0; i<4 ;i++){
        for(int j=0; j<4; j++){
            val=myGame->gameBoard->blocks[i][j]->value;
            if(val==0){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(255, 255, 255);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("");
            }
            else if(val==2){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(187, 173, 160);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("2");
            }
            else if(val==4){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(237, 224, 200);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("4");
            }
            else if(val==8){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(242, 177, 121);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("8");
            }
            else if(val==16){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(245, 149, 99);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("16");
            }
            else if(val==32){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(246, 126, 95);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("32");
            }
            else if(val==64){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(246, 94, 59);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("64");
            }
            else if(val==128){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(237, 207, 114);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("128");
            }
            else if(val==256){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(237, 204, 97);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("256");
            }
            else if(val==512){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(237, 200, 80);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("512");
            }
            else if(val==1024){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(237, 197, 63);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("1024");
            }
            else if(val==2048){
                myBlock[i][j]->setStyleSheet("QLabel { background: rgb(237, 194, 46);color: black; border-style:solid; font: 70pt; font: bold; }");
                myBlock[i][j]->setText("2048");
            }
        }
    }
}
