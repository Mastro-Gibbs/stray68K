#include "ui/axolotlApp.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    QPixmap splashImg(":/icons/img/splash.jpg");
    splash->setPixmap( splashImg );
    splash->show();

    splashImg = splashImg.scaled( 32, 20, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation );

    AxolotlApp w;
    w.setWindowTitle("Stray68K");
    w.setWindowIcon( splashImg );
    w.init();
    w.dynamicBinding();
    w.setIcons();

    QTimer::singleShot( 2500, splash, SLOT(close()) );
    QTimer::singleShot( 2500, &w, SLOT(showMaximized()) );
    QTimer::singleShot( 2500, &w, SLOT(initTheme()) );

    return a.exec();
}
