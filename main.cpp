#include "mainwindow.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(src);
    QApplication a(argc, argv);
    QFont font("Microsoft YaHei", 10);
    a.setFont(font);
    MainWindow w;
    w.show();

    return a.exec();
}
