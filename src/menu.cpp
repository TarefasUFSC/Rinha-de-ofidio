#include "menu.hpp"
#include "ui_menu.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    gameEnv = new GameEnv();
    MenuMusic = new QMediaPlayer(this);
    MenuMusic->setMedia(QUrl("qrc:/sounds/363_full_powershot_0163_preview.mp3"));
    MenuMusic->play();

    background = new QMovie(":/images/MenuBackground.gif");
    ui->BackgroundLabel->setMovie(background);
    background->start();
}

Menu::~Menu()
{
    delete background;
    delete MenuMusic;
    delete ButtonClick;
    delete ui;
}


void Menu::on_StartButton_clicked()
{
    ButtonClick = new QMediaPlayer(this);
    ButtonClick->setMedia(QUrl("qrc:/sounds/mixkit-quick-lock-sound-2854.wav"));
    ButtonClick->play();
    gameEnv->gameExecution(0, MenuMusic);
}

void Menu::on_AboutButton_clicked()
{
    ButtonClick = new QMediaPlayer(this);
    ButtonClick->setMedia(QUrl("qrc:/sounds/mixkit-quick-lock-sound-2854.wav"));
    ButtonClick->play();
    About autores;
    autores.exec();
    //teste do gameover.ui
    //GameOver gameover(nullptr,"5", "3", "1", "100");
    //gameover.exec();
}

void Menu::on_QuitButton_clicked()
{
    ButtonClick = new QMediaPlayer(this);
    ButtonClick->setMedia(QUrl("qrc:/sounds/mixkit-quick-lock-sound-2854.wav"));
    ButtonClick->play();
    Menu::close();
}
