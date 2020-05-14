#include "server.h"
#include "client.h"
#include "iwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    iWidget sample;
    sample.show();

    return a.exec();
}
