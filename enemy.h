#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>

class SnakeModel;
class Enemy : public QObject
{
    Q_OBJECT
public:
    explicit Enemy(SnakeModel *model, QObject *parent = nullptr);
    const QPoint getPosition() const;
signals:
    void snakeIsKilled();
public slots:
    void move();
    void reset();
private:
    const int POSSIBLE_DIRECTIONS_NUMBER = 4;
    QPoint position_ = {0,0};
    SnakeModel *model_;
    double calcDistanceToTheSnake(const QPoint &point);
};

#endif // ENEMY_H
