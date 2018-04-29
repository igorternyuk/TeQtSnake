#include "enemy.h"
#include "snakemodel.h"
#include <QLine>
#include <algorithm>
#include <map>

Enemy::Enemy(SnakeModel *model, QObject *parent) :
    QObject(parent), model_(model)
{}

const QPoint Enemy::getPosition() const
{
    return position_;
}

void Enemy::move()
{
    int curX = position_.x();
    int curY = position_.y();

    std::multimap<double, QPoint> distPosMap;

    QPoint up(curX, curY - 1);
    QPoint down(curX, curY + 1);
    QPoint left(curX - 1, curY);
    QPoint right(curX + 1, curY);
    QPoint allNextPositions[] = { up, down, left, right };

    for(auto &pos: allNextPositions)
    {
        bool isPointInsideOfTheField = !model_->isPointOutsideOfTheField(pos);
        bool isNoWall = !model_->getWallPoints().contains(pos);
        if(isPointInsideOfTheField && isNoWall) {
            distPosMap.insert(std::make_pair(calcDistanceToTheSnake(pos), pos));
        }
    }

    position_ = distPosMap.begin()->second;
    if(model_->getSnakeHeadPosition() == position_)
        emit snakeIsKilled();
}

void Enemy::reset()
{
    position_.setX(0);
    position_.setY(0);
}

double Enemy::calcDistanceToTheSnake(const QPoint &point)
{
    QLineF line(point, model_->getSnakeHeadPosition());
    return line.length();
}
