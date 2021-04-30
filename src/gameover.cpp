#include "gameover.hpp"
#include "ui_gameover.h"
#include <QFontDatabase>
#include <QFont>

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{

}

GameOver::GameOver(QWidget *parent, QString Rounds, QString Normal, QString Boss, QString Food) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
    setWindowTitle(tr("Game Over"));
    movie = new QMovie(":/images/GameOver.gif");
    ui->GameOverLabel->setMovie(movie);
    movie->start();
    ui->RoundsLabel->setText(Rounds);
    ui->NormalLabel->setText(Normal);
    ui->BossLabel->setText(Boss);
    ui->FoodLabel->setText(Food);
}

GameOver::~GameOver()
{
    delete movie;
    delete ui;
}
