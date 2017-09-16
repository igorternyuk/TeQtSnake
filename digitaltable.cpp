#include "digitaltable.h"

digitalTable::digitalTable(int width, int height, int numDigits,
                           QColor color, QWidget *parent) :
    QLCDNumber(numDigits, parent)
{
    this->setFixedSize(width, height);
    this->setAutoFillBackground(true);
    this->setSegmentStyle(QLCDNumber::Flat);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Normal, QPalette::WindowText, color);
    palette.setColor(QPalette::Normal, QPalette::Window, Qt::black);
    this->setPalette(palette);
}

void digitalTable::reset()
{
    display(0);
}

void digitalTable::update(int value)
{
    display(value);
}
