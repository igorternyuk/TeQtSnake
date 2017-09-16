#include "fieldwidget.h"


FieldWidget::FieldWidget(SnakeModel *model, SnakeController *controller, QWidget *parent) :
    QFrame(parent), model_(model), controller_(controller)
{
   setFrameStyle(QFrame::Panel | QFrame::Sunken);
   QPalette palette;
   palette.setColor(QPalette::Background, FIELD_COLOR); // Тут задаем цвет лужайки
   this->setPalette(palette);
   this->setAutoFillBackground(true);
   setFocusPolicy(Qt::StrongFocus);
   setFixedSize(POINT_SIZE * model_->getFieldWidth(), POINT_SIZE * model_->getFieldHeight());  //Убрать волшебные числа
}

void FieldWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    drawWall(painter);
    drawFood(painter);
    drawPoison(painter);
    drawSnake(painter);
    drawEnemy(painter);
    if(model_->isGamePaused())
        drawPauseText(painter);
    if(model_->isGameOver())
        drawGameOverText(painter);
}

void FieldWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_Up :
            controller_->onUpButtonPressed();
            break;
        case Qt::Key_Down :
            controller_->onDownButtonPressed();
            break;
        case Qt::Key_Left :
            controller_->onLeftButtonPressed();
            break;
        case Qt::Key_Right :
            controller_->onRightButtonPressed();
            break;
        case Qt::Key_Space :
            controller_->onSpaceButtonPressed();
            break;
        default:
            QFrame::keyPressEvent(event);
            break;
    }
}

void FieldWidget::drawFood(QPainter &painter)
{
    static const QBrush greenBrush(Qt::green);
    QPoint food = model_->getFoodPosition();
    painter.setBrush(greenBrush);
    painter.drawEllipse(contentsRect().left() + food.x() * POINT_SIZE,
                        contentsRect().top() + food.y() * POINT_SIZE,
                        POINT_SIZE, POINT_SIZE);
}

void FieldWidget::drawPoison(QPainter &painter)
{
    static const QBrush redBrush(Qt::red);
    painter.setBrush(redBrush);
    auto poisonedPoints = model_->getPoisonedPoints();
    for(auto point : poisonedPoints) {
        int x = contentsRect().left() + point.x() * POINT_SIZE;
        int y = contentsRect().top() + point.y() * POINT_SIZE;
        QVector<QPoint> points;
        points.push_back(QPoint(x, y + POINT_SIZE / 2));
        points.push_back(QPoint(x + POINT_SIZE / 2, y));
        points.push_back(QPoint(x + POINT_SIZE, y + POINT_SIZE / 2));
        points.push_back(QPoint(x + 3 * POINT_SIZE / 4, y + POINT_SIZE));
        points.push_back(QPoint(x + POINT_SIZE / 4, y + POINT_SIZE));
        QPolygon polygon(points);
        painter.drawPolygon(polygon);
    }
}

void FieldWidget::drawSnake(QPainter &painter)
{
   //static const int radius = 4;
   static const QBrush blueBrush(Qt::blue);
   static const QBrush cyanBrush(Qt::cyan);
   auto snakePoints = model_->getSnakePoints();
   for(auto i = 0; i < int(snakePoints.size()); ++i) {

       QRect rect(contentsRect().left() + snakePoints[i].x() * POINT_SIZE,
                  contentsRect().top() + snakePoints[i].y() * POINT_SIZE,
                  POINT_SIZE, POINT_SIZE);
       if(i == 0)
           painter.setBrush(blueBrush);
       else
           painter.setBrush(cyanBrush);
       painter.drawEllipse(rect);
       //painter.drawRoundedRect(rect,radius, radius);
   }
}

void FieldWidget::drawEnemy(QPainter &painter)
{
    static const QBrush greenBrush(Qt::black);
    QPoint enemy = model_->getEnemyPosition();
    painter.setBrush(greenBrush);
    painter.drawEllipse(contentsRect().left() + enemy.x() * POINT_SIZE,
                        contentsRect().top() + enemy.y() * POINT_SIZE,
                        POINT_SIZE, POINT_SIZE);
}

void FieldWidget::drawWall(QPainter &painter)
{
    static const QBrush redBricksBrush(QColor(255, 85, 0));
    auto wallPoints = model_->getWallPoints();
    for(auto point :  wallPoints) {
        QRect rect(contentsRect().left() + point.x() * POINT_SIZE,
                   contentsRect().top() + point.y() * POINT_SIZE,
                   POINT_SIZE, POINT_SIZE);
        painter.setBrush(redBricksBrush);
        painter.drawRect(rect);
    }
}

void FieldWidget::drawPauseText(QPainter &painter)
{
    //drawTextFromMatrix(painter, pauseMatrix, TEXT_LEFT, TEXT_TOP, Qt::magenta);
    auto pauseMatrix = model_->getPauseTextCode();
    const QBrush brush(Qt::magenta);
    painter.setBrush(brush);
    for(int i = 0; i < int(pauseMatrix.size()); ++i)
        for(int j = 0; j < int(pauseMatrix[i].size()); ++j)
            if(pauseMatrix[i][j] == 'X')
                painter.drawEllipse(TEXT_LEFT + contentsRect().left() + j * POINT_SIZE,
                                    TEXT_TOP + contentsRect().top() + i * POINT_SIZE,
                                    POINT_SIZE, POINT_SIZE);
}

void FieldWidget::drawGameOverText(QPainter &painter)
{
    auto gameOverMatrix = model_->getGameOverTextCode();
    drawTextFromMatrix(painter, gameOverMatrix, TEXT_LEFT, TEXT_TOP, Qt::yellow);
}

void FieldWidget::drawTextFromMatrix(QPainter &painter, const boolMatrix &matrix,
                                     int left, int top, QColor color)
{
    const QBrush brush(color);
    painter.setBrush(brush);
    for(int i = 0; i < int(matrix.size()); ++i)
        for(int j = 0; j < int(matrix[i].size()); ++j)
            if(matrix[i][j])
                painter.drawEllipse(left + contentsRect().left() + j * POINT_SIZE,
                                    top + contentsRect().top() + i * POINT_SIZE,
                                    POINT_SIZE, POINT_SIZE);
}
