#ifndef MYSPLASHSCREEN_H
#define MYSPLASHSCREEN_H

#include <QSplashScreen>

class MySplashScreen : public QSplashScreen
{
public:
  explicit MySplashScreen(const QPixmap &pixmap = QPixmap(), Qt::WindowFlags f = Qt::WindowFlags());


};

#endif // MYSPLASHSCREEN_H
