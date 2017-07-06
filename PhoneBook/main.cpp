#include "mainwindow.h"
#include "contactdb.h"
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // جهت تنظیم تم ظاهر برنامه
    a.setStyle(QStyleFactory::create("fusion"));

    MainWindow w;
    w.show();

    return a.exec();
}
