
#include "GameOverView.h"

#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>


GameOverView::GameOverView(QMessageBox *parent): QMessageBox(parent)
{

   m_accept = createButton("");
   m_exit = createButton("I'LL BE BACK");


   connect(m_accept, SIGNAL(clicked()), this, SIGNAL(gameStarted()));
   connect(m_exit, SIGNAL(clicked()), this, SIGNAL(gameEnded()));



   this->setStyleSheet("QMessageBox { font: bold; font-size: 36px; border: 6px solid grey; background-color: black; } "
                       "QLabel { color: white; min-width: 240px; min-height: 120px }"
                       "QPushButton { color: white; min-width: 240px }");

   this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);
   this->setDefaultButton(m_accept);

}

GameOverView::~GameOverView()=default;

void GameOverView::levelLost() {
   m_accept->setText("TRY AGAIN!");
    this->setText("<p align=center>Ohh no! You lose!</p>");
    this->setInformativeText("<p align=center>Wanna try again?</p>");
    this->addButton(m_exit,QMessageBox::RejectRole);
    this->addButton(m_accept, QMessageBox::AcceptRole);
    if(!this->exec()) { emit gameEnded(); }
}

void GameOverView::levelDone() {
    m_accept->setText("GO NEXT!");
    this->setText("<p align='center'>Level done, great! </p>");
    this->setInformativeText("<p align='center'>Wanna go next?</p>");
    this->addButton(m_exit,QMessageBox::RejectRole);
    this->addButton(m_accept,QMessageBox::AcceptRole);
    if(!this->exec()) { emit gameEnded(); }
}

QPushButton *GameOverView::createButton(const QString &text)
{
   auto *button = new QPushButton(text);

   button->setDefault(true);

   button->setStyleSheet("QPushButton { font: bold; border: 3px solid darkgrey; border-radius: 20px;"
                         "outline-radius: 20px; font-size: 18px; height: 60px; width: 120px; }"
                         "QPushButton:focus { font: bold; border: 10px solid white; border-radius: 20px;"
                         "outline-radius: 20px; font-size: 18px }");

   return button;
}



