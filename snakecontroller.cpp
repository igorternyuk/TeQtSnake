#include "snakecontroller.h"
#include "snakemodel.h"
#include "snakeview.h"

SnakeController::SnakeController(SnakeModel *model, SnakeView *view, QObject *parent) :
    QObject(parent), model_(model), view_(view)
{}

void SnakeController::onUpButtonPressed()
{
    model_->turnSnake(Direction::UP);
}

void SnakeController::onDownButtonPressed()
{
    model_->turnSnake(Direction::DOWN);
}

void SnakeController::onLeftButtonPressed()
{
    model_->turnSnake(Direction::LEFT);
}

void SnakeController::onRightButtonPressed()
{
    model_->turnSnake(Direction::RIGHT);
}

void SnakeController::onNewGameButtonPressed()
{
     model_->newGame();
}

void SnakeController::onStartButtonPressed()
{
     model_->start();
}

void SnakeController::onPauseButtonPressed()
{
     if(!model_->isGamePaused())
         model_->pause();
     else
         model_->start();
}

void SnakeController::onSpaceButtonPressed()
{
     onPauseButtonPressed();
}

void SnakeController::onAboutButtonPressed()
{

}

void SnakeController::onExitButtonPressed()
{
    view_->close();
}
