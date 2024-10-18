#include "testapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestApp w;
    w.show();

    return app.exec();
}

