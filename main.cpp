#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // 最大化
    w.showMaximized();
    w.show();
    return a.exec();
}
