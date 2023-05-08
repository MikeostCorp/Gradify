///============================================
///
/// Developed by the team: Mikeost Team
/// Link: https://github.com/MikeostCorp/Gradify
/// List of developers: Mikhail Ostashchenko
///                     Andriy Izbash
/// ============================================

#include "preloader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
#if Q_OS_MAC true && Q_OS_MACOS true && Q_OS_MAC64 true && Q_OS_MACX true
    QApplication app(argc, argv);
    preloader window;
    window.show();
    return app.exec();
#else
    qDebug() << "This application is designed specifically for macOS and is optimized for its use. "
                "Please make sure you have it installed on your macOS computer for future use.";
    return 1;
#endif
}
