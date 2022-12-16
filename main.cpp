#include "gamewidget.h"
#include <QApplication>
#include "Maze.h"
#include "Robot.h"
#include <QPainter>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    w.showFullScreen();
//    QLabel *qp = new QLabel;
//    QPixmap *im = new QPixmap(":/images/target.png");
//    qp->setPixmap(*im);
//    qp->showFullScreen();
    return a.exec();
}
