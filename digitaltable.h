#ifndef DIGITALTABLE_H
#define DIGITALTABLE_H

#include <QLCDNumber>

class digitalTable : public QLCDNumber
{
    Q_OBJECT
public:
    static const int DEFAULT_DISPLAY_WIDTH = 120;
    static const int DEFAULT_DISPLAY_HEIGHT = 120;
    static const int NUM_DIGITS = 120;
    digitalTable(int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT,
                 int numDigits = NUM_DIGITS, QColor color = Qt::darkGreen,
                 QWidget *parent = nullptr);
public slots:
    void reset();
    void update(int value);
};

#endif // DIGITALTABLE_H
