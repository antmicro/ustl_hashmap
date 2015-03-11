#include <QtGui/QApplication>
#include "ustl_hashmap.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ustl_hashmap ustl_hashmap;
    ustl_hashmap.show();
    return app.exec();
}
