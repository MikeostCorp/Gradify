///============================================
///
/// Developed by the team: Mikeost Team
/// list of developers: Mikhail Ostashchenko
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
