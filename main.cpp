#include "odisseyradioplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OdisseyRadioPlayer w;
    w.show();
    return a.exec();
}
