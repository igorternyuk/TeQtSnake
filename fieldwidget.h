#ifndef FIELD_H
#define FIELD_H

#include <QFrame>
#include <QKeyEvent>
#include <QPainter>
#include <QRect>
#include <QPoint>
#include "snakemodel.h"
#include "snakecontroller.h"

class FieldWidget : public QFrame
{
    Q_OBJECT
public:
    explicit FieldWidget(SnakeModel *model, SnakeController *controller, QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
private:
    SnakeModel *model_;
    SnakeController *controller_;
    const int POINT_SIZE = 20;
    const int TEXT_LEFT = 20;
    const int TEXT_TOP = 135;
    const QColor FIELD_COLOR = QColor(0,148,255);
    void drawFood(QPainter &painter);
    void drawPoison(QPainter &painter);
    void drawSnake(QPainter &painter);
    void drawEnemy(QPainter &painter);
    void drawWall(QPainter &painter);
    void drawPauseText(QPainter &painter);
    void drawGameOverText(QPainter &painter);
    void drawTextFromMatrix(QPainter &painter, const boolMatrix &matrix, int left, int top, QColor color);
};

#endif // FIELD_H
