///============================================
///
/// Developed by the team: Mikeost Team
/// Link: https://github.com/MikeostCorp/Gradify
/// List of developers: Mikhail Ostashchenko
///                     Andrii Izbash
/// ============================================

#include "preloader.h"

#include <QApplication>
#include <DatabaseHandler/databasehandler.h>

int main(int argc, char *argv[])
{
#if defined(Q_OS_MAC) && defined(Q_OS_MACOS) && defined(Q_OS_MAC64) && defined(Q_OS_MACX)
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
