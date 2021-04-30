#include "gameenv.h"
#include "gameover.hpp"
#include <stdlib.h>
#include <QGraphicsTextItem>
#include <QMediaPlaylist>
#include <QTimer>
#include <QImage>
#include <QBrush>
#include <QMediaPlayer>

#include <QKeyEvent>

GameEnv::GameEnv(QWidget *parent)
{
    foodCount = 0;
    ready = false;
    timer = new QTimer();
    clean();
    musicBg = new QMediaPlayer(this);
    scene->setBackgroundBrush(QBrush(QImage(":/images/GameBackground.png")));

    player = new Snake();
    enemy = new Snake();
    rodada = 0;
    tipo = {"Normal", "Normal", "Boss"};
    state.food.push_back(new Food());
    state.food.push_back(new Food());
    connect(timer, &QTimer::timeout, this, std::bind(&GameEnv::movePlayer, this));
    connect(timer, &QTimer::timeout, this, std::bind(&GameEnv::newGame, this));
    connect(timer, &QTimer::timeout, this, std::bind(&GameEnv::agent, this));
}
void GameEnv::clean()
{
    // criar scene
    //if(scene)
    scene = new QGraphicsScene();
    // fixar o tamanho em 800x600, que é infinito por definição
    scene->setSceneRect(0, 0, 704, 704);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // fixar o tamanho
    setFixedSize(704, 704);
}
void GameEnv::keyPressEvent(QKeyEvent *event)
{
    string dec;
    if (event->key() == Qt::Key_Left)
    {
        // limite para não sair da tela
        dec = "Left";
    }
    else if (event->key() == Qt::Key_Right)
    {
        dec = "Right";
    }
    else if (event->key() == Qt::Key_Up)
    {
        dec = "Up";
    }
    else if (event->key() == Qt::Key_Down)
    {
        dec = "Down";
    }
    if (dec != player->myBody.at(0)->lastAction)
        player->move(dec);
}

void GameEnv::newGame()
{
    player->ready = ready;
    enemy->ready = ready;
    refresh();
    for (size_t j = 0; j < state.food.size(); j++)
    {
        QList<QGraphicsItem *> colliding_item = state.food.at(j)->collidingItems();
        for (int i = 0; i < colliding_item.size(); i++)
        {
            if (typeid(*(colliding_item[i])) == typeid(BodyPart))
            {
                delete state.food.at(j);

                state.food.at(j) = new Food();
                bool achou = false;
                for (BodyPart *part : player->myBody)
                {
                    if (part == colliding_item[i])
                        achou = true;
                }
                if (achou)
                {
                    QMediaPlayer *music = new QMediaPlayer(this);
                    music->setMedia(QUrl("qrc:/Eat.wav"));
                    music->play();
                    player->addNew();
                    foodCount++;
                    int boss = floor(rodada / 3);
                }
                else
                    enemy->addNew();
            }
        }
    }
    if ((player->isVivo && !enemy->isVivo) || player->myBody.size() >= 30)
    {
        delete player;
        delete enemy;
        delete musicBg;
        //cout << "Novo Jogo" << endl;
        QMediaPlayer *music = new QMediaPlayer(this);
        music->setMedia(QUrl("qrc:/GameWin.wav"));
        music->play();
        rodada++;
        gameExecution(rodada);

        return;
    }
    if (!player->isVivo || enemy->myBody.size() >= 30)
    {
        ready = false;
        QMediaPlayer *music = new QMediaPlayer(this);
        music->setMedia(QUrl("qrc:/GameOver.wav"));
        music->play();
        timer->stop();
        delete player;
        delete enemy;
        for (size_t i = 0; i < scene->items().size(); i++)
        {
            scene->items().at(i)->setEnabled(false);
        }
        delete musicBg;
        int boss = floor(rodada / 3);
        GameOver gameover(nullptr, QString::number(rodada), QString::number(rodada - boss), QString::number(boss), QString::number(foodCount));
        gameover.exec();

        hide();
        foodCount = 0;
        if (menuMusic)
            menuMusic->play();
        return;
    }

    refresh();
}
void GameEnv::refresh()
{

    QList<QGraphicsItem *> tel = scene->items();
    for (Food *foo : state.food)
    {
        bool achou = false;
        for (QGraphicsItem *i : tel)
        {
            if (foo == i)
                achou = true;
        }
        if (!achou)
            scene->addItem(foo);
    }
    for (BodyPart *part : player->myBody)
    {
        bool achou = false;
        for (QGraphicsItem *i : tel)
        {
            if (part == i)
                achou = true;
        }
        if (!achou)
            scene->addItem(part);
    }
    for (BodyPart *part : enemy->myBody)
    {
        bool achou = false;
        for (QGraphicsItem *i : tel)
        {
            if (part == i)
                achou = true;
        }
        if (!achou)
            scene->addItem(part);
    }
}
void GameEnv::gameExecution(int r, QMediaPlayer *msc)
{
    menuMusic = msc;
    menuMusic->pause();

    gameExecution(r);
}
void GameEnv::gameExecution(int r)
{

    ready = false;
    startBg = new QGraphicsPixmapItem();
    startBg->setPixmap(QPixmap(":/images/StartScreen.png"));

    rodada = r;

    player = new Snake("Player");
    inimigoAgent = tipo.at(rodada % 3);
    enemy = new Snake(inimigoAgent);
    refresh();
    //clean();

    musicBg = new QMediaPlayer(this);
    musicBg->setMedia(QUrl("qrc:/Game" + inimigoAgent + ".mp3"));
    musicBg->play();
    gameExecution();
    scene->addItem(startBg);
}
void GameEnv::gameExecution()
{

    // adicionar o jogador no cenario
    // criar inimigos

    timer->start(250);

    //QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));

    show();
}
