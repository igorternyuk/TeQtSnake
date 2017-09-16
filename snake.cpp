#include "snake.h"
#include "snakemodel.h"

Snake::Snake(int headX, int headY, int length, Direction direction,
             SnakeModel *model, QObject *parent) :
    QObject(parent), direction_(direction), model_(model)
{
    for(int i = 0; i < length; ++i) {
        QPoint point(headX - i,headY);
        points_.push_back(point);
    }
}

void Snake::setDirection(Direction dir)
{
    if((direction_ == dir) ||
      (abs(static_cast<int>(dir) - static_cast<int>(direction_)) == 2))
          return;
     direction_ = dir;
}

void Snake::move()
{
    // Берем координаты головы змеи
    int nextHeadX = points_.at(0).x();
    int nextHeadY = points_.at(0).y();

    switch(direction_)
    {
        case Direction::UP :
            --nextHeadY;
            break;
        case Direction::DOWN :
            ++nextHeadY;
            break;
        case Direction::LEFT :
            --nextHeadX;
            break;
        case Direction::RIGHT :
            ++nextHeadX;
            break;
        default:
          break;
    }

    // Чтобы змейка при выходе за границы поля появлялась с другой стороны

    if(nextHeadX < 0) nextHeadX = model_->getFieldWidth() - 1;
    if(nextHeadX > model_->getFieldWidth() - 1) nextHeadX = 0;
    if(nextHeadY < 0) nextHeadY = model_->getFieldHeight() - 1;
    if(nextHeadY > model_->getFieldHeight() - 1) nextHeadY = 0;


    QPoint nextHeadPosition(nextHeadX, nextHeadY);
    // Если имеется самопересечение то выходим
    if(isPointInside(nextHeadPosition)) {
         emit snakeHasDied();
         return;
    }
    points_.push_front(nextHeadPosition);
    // Если змея сьела яд то выходим
    for(auto point : model_->getPoisonedPoints())
        if(point == nextHeadPosition) {
            emit snakeHasDied();
            return;
        }
    for(auto point : model_->getWallPoints())
        if(point == nextHeadPosition) {
            emit snakeHasDied();
            return;
        }
    if(nextHeadPosition == model_->getEnemyPosition()) {
        emit snakeHasDied();
        return;
    }
    if(isPointInside(model_->getFoodPosition())) {
        emit foodIsEaten();
    } else
        points_.pop_back();
}

Direction Snake::getDirection() const
{
    return direction_;
}

int Snake::getLength() const
{
    return points_.size();
}

const std::deque<QPoint> Snake::getPoints() const
{
    return points_;
}

bool Snake::isPointInside(QPoint point) const
{
    for(auto p: points_)
        if(p == point)
            return true;
    return false;
}

QPoint Snake::getHead() const
{
    return points_.at(0);
}
