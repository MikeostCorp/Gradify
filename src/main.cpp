///============================================
///
/// Developed by the team: Mikeost Team
/// Education: DSEA DDMA, city Druzkiwka
/// List of developers: Mikhail Ostashchenko
///                     Andriy Izbash
///
/// ============================================

#include "preloader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    preloader w;
    w.show();
    return a.exec();
}
