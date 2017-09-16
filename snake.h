#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <deque>
#include <QPoint>

class SnakeModel;
enum class Direction {LEFT, UP, RIGHT, DOWN};

class Snake : public QObject
{
    Q_OBJECT
public:
    explicit Snake(int headX, int headY, int length, Direction direction,
                   SnakeModel *model, QObject *parent = nullptr);
    void setDirection(Direction dir);
    void move();
    Direction getDirection() const;
    int getLength() const;
    const std::deque<QPoint> getPoints() const;
    bool isPointInside(QPoint point) const;
    QPoint getHead() const;
signals:
    void foodIsEaten();
    void snakeHasDied();
private:
    Direction direction_;
    SnakeModel *model_;
    std::deque<QPoint> points_;

};

#endif // SNAKE_H
