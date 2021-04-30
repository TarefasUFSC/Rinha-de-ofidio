#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <QDialog>
#include <QMovie>

namespace Ui {
class GameOver;
}

class GameOver : public QDialog
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = nullptr);
    GameOver(QWidget *parent = nullptr, QString Rounds = " ", QString Normal = " ", QString Boss = " ", QString Food = " ");
    ~GameOver();

private:
    QMovie *movie;
    Ui::GameOver *ui;
};

#endif // GAMEOVER_HPP
