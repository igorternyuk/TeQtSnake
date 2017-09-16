#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "digitaltable.h"
#include "snakemodel.h"
#include "snakecontroller.h"
#include "fieldwidget.h"

class SnakeView : public QMainWindow
{
    Q_OBJECT
public:
    explicit SnakeView(QWidget *parent = nullptr);
public slots:
    void update();
    void showInfoAbouGame();
private:
    const QString WINDOW_TITLE = "Snake";
    const QString INFO_ABOUT_SNAKE = "Info about snake";
    const int WINDOW_WIDTH = 645;
    const int WINDOW_HEIGHT = 520;
    const int SPACING_BETWEEN_BUTTONS = 20;
    SnakeModel *model_;
    SnakeController *controller_;
    FieldWidget *fieldWidget_;
    digitalTable *scoreLCD_;
    digitalTable *levelLCD_;
    QPushButton *newGameButton_;
    QPushButton *startButton_;
    QPushButton *pauseButton_;
    QPushButton *aboutButton_;
    QPushButton *exitButton_;
    QLabel *createLabel(const QString &text);
};

#endif // SNAKEVIEW_H
