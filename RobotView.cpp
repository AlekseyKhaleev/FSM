
#include "RobotView.h"

#include <QCoreApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include <QTimerEvent>



RobotView::RobotView(const Robot::Model &targetModel, QWidget *parent):
QWidget(parent),
m_viewModel(&targetModel),
m_white(QVector<QImage*>{
        new QImage(":/images/VC_wt_lt"),
        new QImage(":/images/VC_wt_rt"),
        new QImage(":/images/VC_wt_up"),
        new QImage(":/images/VC_wt_dn")
}),
m_green(QVector<QImage*>{
        new QImage(":/images/VC_gr_lt"),
        new QImage(":/images/VC_gr_rt"),
        new QImage(":/images/VC_gr_up"),
        new QImage(":/images/VC_gr_dn")
}),
m_yellow(QVector<QImage*>{
        new QImage(":/images/VC_yw_lt"),
        new QImage(":/images/VC_yw_rt"),
        new QImage(":/images/VC_yw_up"),
        new QImage(":/images/VC_yw_dn")
}),
m_red(QVector<QImage*>{
        new QImage(":/images/VC_rd_lt"),
        new QImage(":/images/VC_rd_rt"),
        new QImage(":/images/VC_rd_up"),
        new QImage(":/images/VC_rd_dn")
})
{
    repaint();
}

void RobotView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    drawRobot();
}
void RobotView::keyPressEvent(QKeyEvent *event){
    emit keyHandled(*event);
}

void RobotView::drawRobot(){
    QPainter qp(this);

    qp.drawImage(QRect(m_viewModel->robotPosition.x() * m_viewModel->dotWidth,
                       m_viewModel->robotPosition.y() * m_viewModel->dotHeight,
                       m_viewModel->dotWidth,
                       m_viewModel->dotHeight),
                 *m_robotSkin[m_viewModel->curColor][m_viewModel->robotDestination]);
}

RobotView::~RobotView(){
    delete m_viewModel;
};


