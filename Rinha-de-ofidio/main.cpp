#include "menu.hpp"

#include <QApplication>
#include <QFontDatabase>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/font/8-bitArcade_In.ttf");
    Menu w;
    w.show();
    return a.exec();
}
