#pragma once

#include <QImage>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QStack>

#include <iostream>
#include <memory>


//inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }


namespace Robot {
    enum Directions {
        LEFT, RIGHT, UP, DOWN
    };

    enum Colors {
        WHITE, GREEN, YELLOW, RED
    };

    struct Model {
        static const int DOT_SIDE{34};
        QString name, state;

        bool scoreIncrease{};
        Colors curColor{}, tmpColor{};
        int score{0}, highScore{0}, steps{};
        Directions robotDestination{};
        QPoint robotPosition;
    };


    class RobotModel : public QObject {
    Q_OBJECT


    public:

        explicit RobotModel(QString name="Robot", QObject *parent = nullptr);

        ~RobotModel() override;

        Robot::Model getModel();

    signals:

        void modelChanged(Robot::Model model);

        void exit(); // state "exit"

    public slots:

        //*****************  FSM STATES *********************************

        void initRobot(); // state "init"

        void setDestination(Robot::Directions dir); // state "rotate"

        void setRobotPosition(QPoint tar_pos); // state "move"

        void animateSkin(); //state "wait"

        void stepBack(); // state "step back"

        //****************************************************************

        void setRobotSteps(int value);

        void setRobotScore(int value);

        void setCurColor(Robot::Colors value);

        void setTmpColor(Robot::Colors value);

        void setScoreIncrease(bool value);

    private:
        Model m_model;
        QStack<Model> m_memory;
    };
}
