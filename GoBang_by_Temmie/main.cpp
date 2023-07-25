#include "mainWindow.h"
#include <QApplication>
#include <QDesktopWidget>
/*--------------------------------------------------------------------------------*/
// 主函数
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.move((QApplication::desktop()->width() - w.width()) / 8,
           (QApplication::desktop()->height() - w.height()) / 4);
    return a.exec();
}
