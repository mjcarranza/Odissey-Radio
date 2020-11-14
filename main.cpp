#include "odisseyradioplayer.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include "MyLinkedList.hpp"
using namespace  std;
/**
 * @brief Main method, modified to launch a QT5 application.
 * @param argc automatically generated argument for the Qt5 application.
 * @param argv automatically generated argument for the Qt5 application.
 * @return execution of the application
 * @author AleQuesada2012
 */
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setStyle("fusion");
    OdisseyRadioPlayer w;
    w.show();
    return a.exec();
}
