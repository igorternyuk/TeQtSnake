#include "snakemodel.h"
#include "enemy.h"

SnakeModel::SnakeModel(QObject *parent) :
    QObject(parent)
{
    createWall();
    newGame();
}

void SnakeModel::turnSnake(Direction dir)
{
    switch(dir) {
      case Direction::UP :
           snake_->setDirection(Direction::UP);
           break;
      case Direction::DOWN :
           snake_->setDirection(Direction::DOWN);
           break;
      case Direction::LEFT :
           snake_->setDirection(Direction::LEFT);
           break;
      case Direction::RIGHT :
           snake_->setDirection(Direction::RIGHT);
           break;
      default:
           break;
    }
    emit updateView();
}

void SnakeModel::timerEvent(QTimerEvent*)
{
    snake_->move();
    emit updateView();
    enemy_->move();
    emit updateView();
}

int SnakeModel::timeoutTime()
{
    return TIMER_TIMEOUT_TIME / (level_ + 1);
}

void SnakeModel::reset()
{
    isGameStarted_ = false;
    isGamePaused_ = false;
    isGameOver_ = false;
    level_ = 1;
    score_ = 0;
    emit levelChanged(1);
    emit scoreChanged(0);
    snake_ = new Snake(START_SNAKE_X, START_SNAKE_Y, START_SNAKE_SIZE,
                   Direction::RIGHT, this);
    enemy_ = new Enemy(this);
    poison_.clear();
    connect(snake_, SIGNAL(foodIsEaten()), this, SLOT(giveFood()));
    connect(snake_, SIGNAL(foodIsEaten()), this, SLOT(scoreAndLevelInc()));
    connect(snake_, SIGNAL(snakeHasDied()), this, SLOT(stop()));
    connect(enemy_, SIGNAL(snakeIsKilled()), this, SLOT(stop()));
    giveFood();
    addPoison();
}


QPoint SnakeModel::generateRandomPoint()
{
    srand(time(NULL));
    return QPoint((rand() % FIELD_WIDTH), (rand() % FIELD_HEIGHT));
}

void SnakeModel::giveFood()
{
    QPoint point;
    do {
        point = generateRandomPoint();
    }while(snake_->isPointInside(point) || poison_.contains(point) ||
           wall_.contains(point));
    food_ = point;
}

void SnakeModel::addPoison()
{
    QPoint point;
    do {
         point = generateRandomPoint();
    }while(snake_->isPointInside(point) || point == food_ ||
           poison_.contains(point) || wall_.contains(point));
    poison_.push_back(point);
}

void SnakeModel::scoreAndLevelInc()
{
    ++score_;
    emit scoreChanged(score_);
    if((score_ >= SCORE_FOR_NEXT_POSION) && (score_ % SCORE_FOR_NEXT_POSION == 0))
    addPoison();
    if((score_ >= NEXT_LEVEL_FOOD_AMOUNT) && (score_ % NEXT_LEVEL_FOOD_AMOUNT == 0))
       ++level_;
    emit levelChanged(level_);
    timer_.start(timeoutTime(),this);
}

void SnakeModel::createWall()
{
    std::vector<std::string> map = getMap();
    for(int i = 0; i < int(map.size()); ++i)
        for(int j = 0; j < int(map[i].size()); ++j) {
            if(map[i][j] == 'X')
                wall_.push_back(QPoint(j, i));
        }
}

std::vector<std::string> SnakeModel::getMap()
{
    static const std::vector<std::string> map = {
    "            X            ",
    "            X            ",
    "            X            ",
    "                         ",
    "    XXXXX XXXXX XXXXX    ",
    "            X            ",
    "                         ",
    "            X            ",
    "            X            ",
    "            X            ",
    "            X            ",
    "            X            ",
    "XXXXX       X       XXXXX",
    "            X            ",
    "            X            ",
    "            X            ",
    "            X            ",
    "            X            ",
    "                         ",
    "            X            ",
    "    XXXXX XXXXX XXXXX    ",
    "                         ",
    "            X            ",
    "            X            ",
    "            X            "};
    return map;
}

bool SnakeModel::isGameStarted() const
{
    return isGameStarted_;
}

bool SnakeModel::isGamePaused() const
{
    return isGamePaused_;
}

bool SnakeModel::isGameOver() const
{
    return isGameOver_;
}

bool SnakeModel::isPointOutsideOfTheField(const QPoint &point) const
{
    return point.x() < 0 || point.x() > FIELD_WIDTH - 1 ||
       point.y() < 0 || point.y() > FIELD_HEIGHT - 1;
}

const std::deque<QPoint> SnakeModel::getSnakePoints() const
{
    return snake_->getPoints();
}

const QPoint SnakeModel::getSnakeHeadPosition() const
{
    return snake_->getHead();
}

const QPoint SnakeModel::getEnemyPosition() const
{
    return enemy_->getPosition();
}

const QList<QPoint> SnakeModel::getPoisonedPoints() const
{
    return poison_;
}

const QList<QPoint> SnakeModel::getWallPoints() const
{
    return wall_;
}

const QPoint SnakeModel::getFoodPosition() const
{
    return food_;
}

int SnakeModel::getFieldHeight() const
{
    return FIELD_HEIGHT;
}

int SnakeModel::getFieldWidth() const
{
    return FIELD_WIDTH;
}

void SnakeModel::start()
{
    if(!isGameOver_) {
        if(!isGameStarted_)
            isGameStarted_ = true;
        isGamePaused_ = false;
        emit updateView();
        timer_.start(timeoutTime(),this);
    }
}

void SnakeModel::pause()
{
    if(!isGameStarted_ || isGameOver_) return;
    isGamePaused_ = true;
        timer_.stop();
    emit updateView();
}

void SnakeModel::stop()
{
    timer_.stop();
    isGameOver_ = true;
    emit updateView();
    return;
}

void SnakeModel::newGame()
{
    if(timer_.isActive())
        timer_.stop();
    reset();
    emit updateView();
}

std::vector< std::string > SnakeModel::getPauseTextCode() const
{
    static const std::vector< std::string > GAME_PAUSED_TEXT_CODE = {
        "  XXX  XX X X XXX XXX ",
        "  X X X X X X X   X   ",
        "  XXX XXX X X XXX XXX ",
        "  X   X X X X   X X   ",
        "  X   X X XXX XXX XXX "
    };
    return GAME_PAUSED_TEXT_CODE;
}

boolMatrix SnakeModel::getGameOverTextCode() const
{
    static const boolMatrix GAME_OVER_TEXT_CODE = {
        {0,0,1,1,0,0,0,1,1,1,0,1,1,1,1,0,0,1,1,1,1,0},
        {0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0},
        {0,1,0,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0},
        {0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0},
        {0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,1,1,1,1,0,1},
        {0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1},
        {0,1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,1,1,1,1,0,1},
        {0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0},
        {0,1,1,1,1,0,1,1,0,0,0,1,1,1,1,0,1,0,0,1,0,1}
    };
    return GAME_OVER_TEXT_CODE;
}

