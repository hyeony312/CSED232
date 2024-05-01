#include "blockui.h"

BlockUi::BlockUi(QWidget *parent) : QLabel(parent)
{
    setFixedSize(250, 250);
    setStyleSheet("QLabel { background: rgb(255, 255, 255); color: black; border-style: solid; font: bold 70pt; }");
    setAlignment(Qt::AlignCenter);
}
