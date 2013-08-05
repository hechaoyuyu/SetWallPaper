#include "mainwindow.h"
#include "setpaper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("StartOS");
    QCoreApplication::setApplicationName("SetWallpaper");
    QCoreApplication::setOrganizationDomain("www.startos.org");

    QApplication app(argc, argv);

    //i18n
    QTranslator ts;
    ts.load(":/lang/" + QLocale::system().name());
    app.installTranslator(&ts);

    MainWindow window;
    window.show();
    
    return app.exec();
}
