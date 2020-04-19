#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
#include <QStringLiteral>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle(QStringLiteral("获取文件夹内制定类型文件的名称"));
    w.setWindowIcon(QIcon(":/icon/images/icon.png"));
    w.show();


    return a.exec();
}
