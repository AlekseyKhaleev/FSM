
#include "Controller.h"


#include <QCoreApplication>
#include <QKeyEvent>
#include <QTextStream>
#include <QTime>
#include <utility>

#include "../HighscoresWidget.h"


using namespace Highscores;

void Controller::keyEventAction(int eventKey) {
    switch (eventKey) {
        case Qt::Key_Left: {
            if(m_robotModel.robotDestination!=Robot::Directions::LEFT){
                emit robotRotated(Robot::Directions::LEFT, checkEnergy());
            }
            break;
        }
        case Qt::Key_Right:{
            if(m_robotModel.robotDestination!=Robot::Directions::RIGHT){
                emit robotRotated(Robot::Directions::RIGHT, checkEnergy());
            }
            break;
        }
        case Qt::Key_Up:{
            if(m_robotModel.robotDestination!=Robot::Directions::UP){
                emit robotRotated(Robot::Directions::UP, checkEnergy());
            }
            break;
        }
        case Qt::Key_Down:{
            if(m_robotModel.robotDestination!=Robot::Directions::DOWN){
                emit robotRotated(Robot::Directions::DOWN, checkEnergy());
            }
            break;
        }
        case Qt::Key_Space:{
            moveRobot();
            break;
        }
        case Qt::Key_Backspace:{
            emit stepBack();
            break;
        }
        case Qt::Key_Escape:{
            emit returnClicked();
            break;
        }
        default:break;
    }
    if(m_robotModel.steps == m_mazeModel.maxEnergy) { emit levelDone(false); }
}



void Controller::updateMazeModel(Maze::Model model) {
    m_mazeModel = std::move(model);
}



void Controller::updateRobotModel(Robot::Model model) {
    m_robotModel = std::move(model);
    if(getPercentEnergy() || (m_robotModel.steps == m_mazeModel.maxEnergy)){ emit energyChanged(getPercentEnergy()); }

}



Controller::Controller(Robot::Model robotModel, Maze::Model mazeModel, QObject *parent) :
    QObject(parent), m_robotModel(std::move(robotModel)), m_mazeModel(std::move(mazeModel))
{
    scoreIncrease = true;
    m_animationTimerId = startTimer(m_animationDelay);
}


Controller::~Controller()=default;



void Controller::timerEvent(QTimerEvent *event) {
    if(event->timerId()==m_animationTimerId){
        emit skinAnimated();
    }
}


bool Controller::checkWall(QPoint dest) const{
    return !m_mazeModel.walls.contains(dest);
}


int Controller::getPercentEnergy() const{
    return (((m_mazeModel.maxEnergy - m_robotModel.steps) * 100) / m_mazeModel.maxEnergy);
}


int Controller::updateScore() const
{
    if (scoreIncrease)
        return (m_robotModel.score + 1);
    else if (m_robotModel.score) {
        return (m_robotModel.score - 1);
    }
    else {return (m_robotModel.score);}
}


void Controller::checkBattery()
{
    if (m_mazeModel.batteries.contains(m_robotModel.robotPosition)) {
        scoreIncrease = false;
        emit batteryFound(m_robotModel.robotPosition);
        emit energyChanged(getPercentEnergy());

    }
}


void Controller::checkTarget(){
    if (m_robotModel.robotPosition == m_mazeModel.targetPosition) {
       writeHighscore();
       emit levelDone(true);
    }
}

void Controller::writeHighscore() const{
   auto *HSFile = new QFile("../resources/highscores.txt");
   if (!HSFile->open(QIODevice::ReadOnly | QIODevice::Text)){return;}
   QVector<Line> lines;
   while(!HSFile->atEnd()) {
      QString lineName = HSFile->readLine();
      lineName.remove('\n');
      QString lineScore = HSFile->readLine();
      lineName.remove('\n');
      lines.push_back(Line(lineName, lineScore.toInt()));
   }
   lines.push_back(Line(m_robotModel.name, m_robotModel.score));

   std::sort(lines.begin(), lines.end(), compareLines);

   HSFile->close();
   if (HSFile->open(QIODevice::WriteOnly | QIODevice::Text))
   {
      QTextStream out(HSFile);
      if (lines.size() < 10)
      {
         for (auto &i: lines) { out << i.NAME << '\n' << i.SCORE << '\n'; }
      } else
      {
         for (int i = 0; i < 10; i++) { out << lines[i].NAME << '\n' << lines[i].SCORE << '\n'; }
      }
      HSFile->close();
   }
}

void Controller::locateBattery(){
    QPoint battery;
    do{
        battery = getRandDot();
    } while ((m_robotModel.robotPosition == battery) || (m_mazeModel.targetPosition == battery)
             || (abs(battery.x() - m_robotModel.robotPosition.x()) > m_mazeModel.fieldWidth / 4)
             || (abs(battery.y() - m_robotModel.robotPosition.y()) > m_mazeModel.fieldHeight / 2));
    emit batteryLocated(battery);
}


void Controller::moveRobot(){
    QPoint tar_pos = m_robotModel.robotPosition;
    switch (m_robotModel.robotDestination) {
        case Robot::LEFT: {
            tar_pos.rx()-=1;
            if (checkWall(tar_pos)) {
                emit robotMoved(tar_pos, updateScore(), checkEnergy());
            }
            break;
        }
        case Robot::RIGHT:{
            tar_pos.rx()+=1;
            if (checkWall(tar_pos)) {
                emit robotMoved(tar_pos, updateScore(), checkEnergy());
            }
            break;
        }
        case Robot::UP:{
            tar_pos.ry()-=1;
            if (checkWall(tar_pos)) {
                emit robotMoved(tar_pos, updateScore(), checkEnergy());
            }
            break;
        }
        case Robot::DOWN:{
            tar_pos.ry()+=1;
            if (checkWall(tar_pos)) {
                emit robotMoved(tar_pos, updateScore(), checkEnergy());
            }
            break;
        }
        default: break;
    }
    checkTarget();
    checkBattery();

}


QPoint Controller::getRandDot() const {
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    do{
        dot.rx() = rand() % m_mazeModel.fieldWidth;
        dot.ry() = rand() % m_mazeModel.fieldHeight;
    }while(m_mazeModel.walls.contains(dot));
    return dot;
}


Robot::Colors Controller::checkEnergy()
{
    int curEnergy = getPercentEnergy();
    if(m_robotModel.steps == m_mazeModel.maxEnergy){
        return Robot::WHITE;
    }


    if ((curEnergy <= 70) && ((m_robotModel.curColor == Robot::GREEN)||(m_robotModel.tmpColor == Robot::GREEN))) {
        locateBattery();
        return (Robot::YELLOW);
    }
    if((curEnergy <= 30) && ((m_robotModel.curColor == Robot::YELLOW)||(m_robotModel.tmpColor == Robot::YELLOW))){
        locateBattery();
        return (Robot::RED);
    }
    return (m_robotModel.tmpColor == Robot::WHITE? m_robotModel.curColor:m_robotModel.tmpColor);
}


