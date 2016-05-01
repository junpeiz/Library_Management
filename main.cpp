#include "mainwindow.h"
#include <QApplication>
#include <QPushbutton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("图书管理系统  ———By 周君沛");
    w.show();

    return a.exec();
}
