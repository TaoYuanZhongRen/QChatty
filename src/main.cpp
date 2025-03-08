#include "../header/mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication a(argc, argv);

    QFile qss("D:/Code/QChatty/style/stylesheet.qss");
    if (qss.open(QFile::ReadOnly))
    {
        qDebug() << "Success to open qss file";
        QString styleSheet = QLatin1String(qss.readAll());
        a.setStyleSheet(styleSheet);
        qss.close();
    }
    else
    {
        qDebug() << "Failed to open qss file";
    }

    MainWindow w;

    //QDesktopWidget* pDesktopWidget = QApplication::desktop();
    ////获取可用桌面大小
    //QRect deskRect = QApplication::desktop()->availableGeometry();
    //qDebug() << "deskRect:" << deskRect.x() << " " << deskRect.y() << endl;
    ////获取主屏幕分辨率
    //QRect screenRect = QApplication::desktop()->screenGeometry();
    //qDebug() << "screenRect:" << screenRect.x() << " " << screenRect.y() << endl;
    ////获取屏幕数量
    //int nScreenCount = QApplication::desktop()->screenCount();
    //qDebug() << "nScreenCount:" << nScreenCount << endl;

    //QScreen* screen = QGuiApplication::primaryScreen();
    ////获取当前实际屏幕大小
    //QRect rect1 = screen->geometry();
    //qDebug() << "rect1" << rect1.size().width() << rect1.size().height();
    //qDebug() << rect1.topLeft();
    //qDebug() << rect1.bottomRight();
    ////获取当前实际可用屏幕大小（去掉下边框）
    //QRect rect2 = screen->availableGeometry();
    //qDebug() << "rect2" << rect2.size().width() << rect2.size().height();
    //qDebug() << rect2.topLeft();
    //qDebug() << rect2.bottomRight();

    //int screen_width = rect2.size().width() * 0.75;    //设置可显示部分比例
    //int screen_height = rect2.size().height() * 0.75;  //设置可显示部分比例


    //w.resize(screen_width, screen_height);

    w.show();
    return a.exec();
}
