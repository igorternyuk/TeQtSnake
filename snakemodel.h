#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <ctime>
#include <cmath>
#include <vector>
#include <QBasicTimer>
#include <QPoint>
#include <QDebug>
#include "snake.h"

class Enemy;

typedef std::vector< std::vector< bool > > boolMatrix;

class SnakeModel : public QObject
{
    Q_OBJECT
public:
    explicit SnakeModel(QObject *parent = nullptr);
    bool isGameStarted() const;
    bool isGamePaused() const;
    bool isGameOver() const;
    int  getScore() const;
    bool isPointOutsideOfTheField(const QPoint &point) const;
    const std::deque<QPoint> getSnakePoints() const;
    const QPoint getSnakeHeadPosition() const;
    const QPoint getEnemyPosition() const;
    const QList<QPoint> getPoisonedPoints() const;
    const QList<QPoint> getWallPoints() const;
    const QPoint getFoodPosition() const;
    int getFieldHeight() const;
    int getFieldWidth() const;
    boolMatrix getGameOverTextCode() const;
    std::vector<std::string> getPauseTextCode() const;
signals:
    void updateView();
    void scoreChanged(int currentScore);
    void levelChanged(int currentLevel);
public slots:
    void start();
    void pause();
    void newGame();
    void turnSnake(Direction dir);
protected:
    void timerEvent(QTimerEvent*) Q_DECL_OVERRIDE;
private:
    const int FIELD_WIDTH = 25;
    const int FIELD_HEIGHT = 25;
    const int START_SNAKE_SIZE = 6;
    const int START_SNAKE_X = 5;
    const int START_SNAKE_Y = 12;
    const int TIMER_TIMEOUT_TIME = 800;
    const int NEXT_LEVEL_FOOD_AMOUNT = 10;
    const int SCORE_FOR_NEXT_POSION = 3;
    bool isGameStarted_ = false;
    bool isGamePaused_ = false;
    bool isGameOver_ = false;
    int level_ = 1;
    int score_ = 0;
    Snake *snake_ = nullptr;
    Enemy *enemy_ = nullptr;
    QPoint food_ = {-1, -1};
    QList<QPoint> poison_;
    QList<QPoint> wall_;
    QBasicTimer timer_;
    int timeoutTime();
    void reset();
    void addPoison();
    QPoint generateRandomPoint();
private slots:
    void stop();
    void giveFood();
    void scoreAndLevelInc();
    void createWall();
    std::vector<std::string> getMap();
};

#endif // SNAKEMODEL_H
