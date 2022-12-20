#include "gamewidget.h"

#include <QCoreApplication>
#include <QLayout>
#include <QLCDNumber>
#include <QStackedLayout>

#include "energywidget.h"
#include "RobotModel.h"
#include "MazeModel.h"

GameWidget::GameWidget(QWidget *parent):
QWidget{parent},
m_mazeModel(new Maze::MazeModel)
//m_robotModel(new RobotModel(m_mazeModel->getMazeModel())),
//m_robotController(new RobotController{m_robot->getRobotModel(), m_robot->getMazeModel()}),
//m_robotView(new RobotView{m_robot->getRobotModel()}),
//m_energyStatus(new EnergyWidget)
{
    m_robotModel = new Robot::RobotModel(m_mazeModel->getMazeModel());
    m_robotController = new RobotController{m_robotModel->getRobotModel(), m_mazeModel->getMazeModel()};
    m_robotView = new RobotView{m_robotModel->getRobotModel()};
    m_mazeView = new MazeView{m_mazeModel->getMazeModel()};

    this->setStyleSheet("QWidget {background-color: black; color: WHITE;}");

    m_robotView->setFocusPolicy(Qt::StrongFocus);
    m_robotView->setStyleSheet("RobotView {background-color: WHITE; color: black;}");

    m_mazeView->setStyleSheet("MazeView {background-color: WHITE; color: black;}");

    m_scoreLcd = new QLCDNumber(4);
    m_scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    m_levelLcd = new QLCDNumber(4);
    m_levelLcd->setSegmentStyle(QLCDNumber::Filled);

    connect(m_robotController, SIGNAL(skinAnimated()), m_robotModel, SLOT(animateSkin()));

    connect(m_mazeModel, SIGNAL(modelChanged()), m_mazeView, SLOT(repaint()));

    connect(m_robotView, SIGNAL(keyHandled(QKeyEvent)),
            m_robotController, SLOT(keyEventAction(QKeyEvent)));

    connect(m_robotModel, SIGNAL(modelChanged()),
            m_robotView, SLOT(updateModel()));

    connect(m_robotController, SIGNAL(inGameChanged(bool)),
            m_robotModel, SLOT(setInGame(bool)));

    connect(m_robotController, SIGNAL(robotScoreChanged(int)),
            m_robotModel, SLOT(setRobotScore(int)));

    connect(m_robotController, SIGNAL(tmpColorChanged(Robot::Colors)),
            m_robotModel, SLOT(setTmpColor(Robot::Colors)));

    connect(m_robotController, SIGNAL(curColorChanged(Robot::Colors)),
            m_robotModel, SLOT(setCurColor(Robot::Colors)));

    connect(m_robotController, SIGNAL(robotEnergyChanged(int)),
            m_robotModel, SLOT(setRobotEnergy(int)));

    connect(m_robotController, SIGNAL(batteryFinded(QPoint)),
            m_mazeModel, SLOT(delBattery(QPoint)));

    connect(m_robotController, SIGNAL(batteryLocated(QPoint)),
            m_mazeModel, SLOT(addBattery(QPoint)));

    connect(m_robotController, SIGNAL(destinationChanged(Robot::Directions)),
            m_robotModel, SLOT(setDestination(Robot::Directions)));

    connect(m_robotController, SIGNAL(mazeStateChanged(Maze::Model)),
            m_mazeModel, SLOT(setMazeState(Maze::Model)));

    connect(m_robotController, SIGNAL(robotPositionChanged(QPoint)),
            m_robotModel, SLOT(setRobotPosition(QPoint)));

    connect(m_robotController, SIGNAL(robotStateChanged(Robot::Model)),
            m_robotModel, SLOT(setRobotState(Robot::Model)));

    connect(m_robotController, SIGNAL(robotStepsChanged(int)),
            m_robotModel, SLOT(setRobotSteps(int)));

    connect(m_robotController, SIGNAL(scoreIncreaseChanged(bool)),
            m_robotModel, SLOT(setScoreIncrease(bool)));

//    connect(m_robotModel, SIGNAL(energyChanged(int)),
//            m_energyStatus, SLOT(setEnergyStatus(int)));
//    connect(m_robotModel, &RobotModel::scoreChanged,
//            m_scoreLcd, qOverload<int>(&QLCDNumber::display));
//    connect(m_robot, &RobotModel::levelChanged,
//            m_levelLcd, qOverload<int>(&QLCDNumber::display));

    auto gameLay = new QStackedLayout;
    gameLay->setStackingMode(QStackedLayout::StackAll);
    gameLay->addWidget(m_mazeView);
    gameLay->addWidget(m_robotView);

    auto *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("<b>ENERGY</b>")), 0, 0, 2, 1);
//    layout->addWidget(m_energyStatus,2,0,3,1);
    layout->addWidget(createLabel(tr("<b>LEVEL</b>")), 0, 1, 2, 1);
//    layout->addWidget(m_levelLcd, 2, 1, 3, 1);
    layout->addWidget(createLabel(tr("<b>SCORE</b>")), 0, 2, 2, 1);
//    layout->addWidget(m_scoreLcd, 2, 2, 3, 1);
    layout->addLayout(gameLay, 6, 0, 20, 3);
//    layout->addLayout(gameLay, 6, 0, 20, 3);

    setLayout(layout);
    setWindowTitle(tr("RobotModel"));
}

QLabel *GameWidget::createLabel(const QString &text){
    auto *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    return label;
}
