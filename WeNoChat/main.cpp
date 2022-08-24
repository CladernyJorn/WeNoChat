#include "UI/login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout<<Encoder_login("hxy","handsome")<<std::endl;
    if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
            QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//for avoiding the different DPI of equipments
    QApplication a(argc, argv);
    //login w;
    //w.show();
    MainWindow w;
    w.show();
    return a.exec();
}
