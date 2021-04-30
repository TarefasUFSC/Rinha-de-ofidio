#ifndef ABOUT_HPP
#define ABOUT_HPP

#include <QDialog>
#include <QMovie>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    QMovie *movie;
    Ui::About *ui;
};

#endif // ABOUT_HPP
