#include "snakeview.h"

SnakeView::SnakeView(QWidget *parent) :
    QMainWindow(parent)
{
    model_ = new SnakeModel();
    controller_ = new SnakeController(model_, this);
    fieldWidget_ = new FieldWidget(model_, controller_);
    scoreLCD_ = new digitalTable(120,40,5,Qt::green);
    levelLCD_ = new digitalTable(120,40,5,Qt::red);
    levelLCD_->update(1);
    newGameButton_ = new QPushButton("NewGame");
    newGameButton_->setFocusPolicy(Qt::NoFocus);
    startButton_ = new QPushButton("Start");
    startButton_->setFocusPolicy(Qt::NoFocus);
    pauseButton_ = new QPushButton("Pause");
    pauseButton_->setFocusPolicy(Qt::NoFocus);
    aboutButton_ = new QPushButton("About");
    aboutButton_->setFocusPolicy(Qt::NoFocus);
    exitButton_ = new QPushButton("Exit");
    exitButton_->setFocusPolicy(Qt::NoFocus);
    QVBoxLayout *rightVBoxLayout = new QVBoxLayout;
    rightVBoxLayout->setSpacing(SPACING_BETWEEN_BUTTONS);
    rightVBoxLayout->addWidget(createLabel("SCORE"));
    rightVBoxLayout->addWidget(scoreLCD_);
    rightVBoxLayout->addWidget(createLabel("LEVEL"));
    rightVBoxLayout->addWidget(levelLCD_);
    rightVBoxLayout->addWidget(newGameButton_);
    rightVBoxLayout->addWidget(startButton_);
    rightVBoxLayout->addWidget(pauseButton_);
    rightVBoxLayout->addWidget(aboutButton_);
    rightVBoxLayout->addWidget(exitButton_);
    rightVBoxLayout->insertStretch(-1);
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(fieldWidget_);
    hBoxLayout->addLayout(rightVBoxLayout);
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(hBoxLayout);
    this->setCentralWidget(centralWidget);
    this->setWindowTitle(WINDOW_TITLE);
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    connect(newGameButton_, SIGNAL(clicked(bool)), controller_, SLOT(onNewGameButtonPressed()));
    connect(startButton_, SIGNAL(clicked(bool)), controller_, SLOT(onStartButtonPressed()));
    connect(pauseButton_, SIGNAL(clicked(bool)), controller_, SLOT(onPauseButtonPressed()));
    connect(aboutButton_, SIGNAL(clicked(bool)), this, SLOT(showInfoAbouGame()));
    connect(exitButton_, &QPushButton::clicked, [&](){close();});
    connect(model_, SIGNAL(updateView()), this, SLOT(update()));
    connect(model_, SIGNAL(scoreChanged(int)), scoreLCD_, SLOT(update(int)));
    connect(model_, SIGNAL(levelChanged(int)), levelLCD_, SLOT(update(int)));
}

void SnakeView::update()
{
    fieldWidget_->update();
}

void SnakeView::showInfoAbouGame()
{
    QMessageBox msg;
    msg.setText(INFO_ABOUT_SNAKE);
    msg.exec();
}

QLabel *SnakeView::createLabel(const QString &text)
{
   QLabel *label = new QLabel(text);
   label->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
   return label;
}
