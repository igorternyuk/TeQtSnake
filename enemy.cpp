#include "enemy.h"
#include "snakemodel.h"
#include <algorithm>

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
     // Вектор пар из четырех возможных следующих позиций врага (позиция определяется через QPoint) и
    // соответсвующих им расстояниям
    // до головы змеи. Вибирается минимальное при этом проверяется критерий отсутсвия столкновений со
    // стенкой и нахождение в пределах поля
    QVector< QPair< QPoint, double > > movements;

    QPoint up(curX, curY - 1);
    QPair<QPoint, double> moveUp(up, calcDistanceToTheSnake(up));
    movements.push_back(moveUp); // UP

    QPoint down(curX, curY + 1);
    QPair<QPoint, double> moveDown(down, calcDistanceToTheSnake(down));
    movements.push_back(moveDown); // DOWN

    QPoint left(curX - 1, curY);
    QPair<QPoint, double> moveLeft(left, calcDistanceToTheSnake(left));
    movements.push_back(moveLeft); // LEFT

    QPoint right(curX + 1, curY);
    QPair<QPoint, double> moveRight(right, calcDistanceToTheSnake(right));
    movements.push_back(moveRight); // RIGHT

    std::sort(movements.begin(), movements.end(),
              [](const auto &p1, const auto &p2){ return p1.second < p2.second;});

    for(auto m : movements) {
        bool isPointInsideOfTheField = !model_->isPointOutsideOfTheField(m.first);
        bool isNoWall = !model_->getWallPoints().contains(m.first);
        if(isPointInsideOfTheField && isNoWall) {
            position_ = m.first;
            break;
        }
    }
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
    auto snake = model_->getSnakePoints();
    auto curSnakeX = snake.at(0).x();
    auto curSnakeY = snake.at(0).y();
    return (curSnakeX - point.x()) * (curSnakeX - point.x()) +
            (curSnakeY - point.y()) * (curSnakeY - point.y());
}
