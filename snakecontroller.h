#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include <QObject>

class SnakeView;
class SnakeModel;

class SnakeController : public QObject
{
    Q_OBJECT
public:
    explicit SnakeController(SnakeModel *model, SnakeView *view, QObject *parent = nullptr);
public slots:
    void onUpButtonPressed();
    void onDownButtonPressed();
    void onLeftButtonPressed();
    void onRightButtonPressed();
    void onNewGameButtonPressed();
    void onStartButtonPressed();
    void onPauseButtonPressed();
    void onSpaceButtonPressed();
    void onAboutButtonPressed();
    void onExitButtonPressed();
private:
    SnakeModel *model_;
    SnakeView *view_;
};

#endif // SNAKECONTROLLER_H
