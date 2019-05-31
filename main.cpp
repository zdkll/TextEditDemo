#include "texteditwidget.h"
#include <QApplication>

#include <mysplashscreen.h>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/images/splash.jpg");
    MySplashScreen  splashScreen(pixmap);

    splashScreen.show();

    TextEditWidget w;
    QTime t;
    int n = 10;
    while(n--){
        t.start();
        while(t.elapsed()<10){
            a.processEvents();
            if(n%10 == 0)
                splashScreen.showMessage("Loaded modules "+QString::number(n));
        }
    }

    w.show();
    splashScreen.finish(&w);

    return a.exec();
}
