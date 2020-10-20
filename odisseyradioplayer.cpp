#include "odisseyradioplayer.h"
#include "ui_odisseyradioplayer.h"
#include <QVBoxLayout>
#include <fstream>
#include <iostream>
#include <sstream>
#include "MyLinkedList.hpp"

using namespace std;

OdisseyRadioPlayer::OdisseyRadioPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OdisseyRadioPlayer)
{
    ui->setupUi(this);

    // LinkedList instance
    auto *lines = new MyLinkedList<string>;
    string line;
    // Opening csv file
    ifstream myFile("/home/mario/Escritorio/fma_metadata/raw_genres.csv"); // Change to use with raw_tracks.csv
    // Reading csv file
    if (myFile.is_open()) {
        while (getline(myFile, line, ',')) {
            lines->add(line);
        }
        myFile.close();
    }
    else cout << "Unable to open file";

    // Loading song data to the UI
    int index = 1;
    int fil = 0;
    for (int i=0; i<lines->getLen() ; i++) {
        if (4*index==i){
            // Filling out the song`s name column
            QString InsertingData1 = lines->get(i).data();
            ui->SongTable->insertRow(ui->SongTable->rowCount()); // Add row
            ui->SongTable->setItem(ui->SongTable->rowCount()-2,0, new QTableWidgetItem(InsertingData1)); // Add data

            // Filling out the song`s lenght column
            QString InsertingData2 = lines->get(i-1).data();
            ui->SongTable->setItem(ui->SongTable->rowCount()-2,1, new QTableWidgetItem(InsertingData2)); // Add data

            // Filling out the song`s artist column
            QString InsertingData3 = lines->get(i-2).data();
            ui->SongTable->setItem(ui->SongTable->rowCount()-2,2, new QTableWidgetItem(InsertingData3)); // Add data

            // Filling out the song`s genre column
            QString InsertingData4 = lines->get(i-3).data();
            ui->SongTable->setItem(ui->SongTable->rowCount()-2,3, new QTableWidgetItem(InsertingData4)); // Add data

            index++;
            fil++;
        }
    }

}

OdisseyRadioPlayer::~OdisseyRadioPlayer()
{
    delete ui;
}

void OdisseyRadioPlayer::on_PlayPauseBtn_clicked()
{

}
