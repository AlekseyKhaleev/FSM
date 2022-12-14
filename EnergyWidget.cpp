#include "EnergyWidget.h"
#include <QPainter>
#include <QWidget>
#include <QObject>


EnergyWidget::EnergyWidget(QWidget *parent)
        : QWidget{parent}
{

    connect(this, SIGNAL(statusChanged()), this, SLOT(repaint()));
}

EnergyWidget::~EnergyWidget()=default;

void EnergyWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    drawStatus();
}



void EnergyWidget::setEnergyStatus(int energy){
    if(energy == 0)       {m_enStatus = en_0; }
    else if(energy <= 10) {m_enStatus = en_10; }
    else if(energy <= 30) {m_enStatus = en_30; }
    else if(energy <= 50) {m_enStatus = en_50; }
    else if(energy <= 70) {m_enStatus = en_70; }
    else if(energy <= 80) {m_enStatus = en_80; }
    else                  {m_enStatus = en_90; }
    emit statusChanged();
}

void EnergyWidget::drawStatus(){
    QPainter qp(this);
    qp.drawPixmap(this->width()/2-this->width()*0.3, 0,
                  this->width()*0.6,this->height(),m_enStatusPM[m_enStatus]);
}
