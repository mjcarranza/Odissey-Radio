#include "odisseyradioplayer.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include "MyLinkedList.hpp"
using namespace  std;

int main(int argc, char *argv[])
{
    auto *lines = new MyLinkedList<string>;
    string line;
    ifstream myFile("test.csv");
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            lines->add(line);
        }
        myFile.close();
    }
    else cout << "Unable to open file";
    for (int i = 0; i < lines->getLen(); ++i) {
        cout << lines->get(i) << endl;
    }

    QApplication a(argc, argv);
    OdisseyRadioPlayer w;
    w.show();
    return a.exec();
}
