#include <QApplication>
#include "SimpleZipperUI.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    SimpleZipperUI simpleZipperUI;
    simpleZipperUI.show();
    return app.exec();
}
