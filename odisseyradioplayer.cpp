#include "odisseyradioplayer.h"
#include "ui_odisseyradioplayer.h"
#include <QVBoxLayout>
#include <fstream>
#include <iostream>
#include <QMouseEvent>
#include <QWidget>
#include "MyLinkedList.hpp"

using namespace std;
auto *libs = new MyLinkedList<string>;
QVBoxLayout *libLayout = new QVBoxLayout();
OdisseyRadioPlayer::OdisseyRadioPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OdisseyRadioPlayer)
{
    // Update user interface
    ui->setupUi(this);
}

OdisseyRadioPlayer::~OdisseyRadioPlayer()
{
    delete ui;
}

// this method is exectuted when clicking a song`s genre label
void OdisseyRadioPlayer::loadSongs(){

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
        }
    }
}

void OdisseyRadioPlayer::mousePressEvent(QMouseEvent *ev)
{
    // Cursor positions
    int X = ev->x();
    int Y = ev->y();
    //cout<<"esto si funciona "<<endl;
    // Label to show each genre`s name.
    QLabel *gLabel = new QLabel();
    // Linked list


    // If the Library is empty -> fill it out.
    if(libs->getLen()==0){
        // LinkedList instance
        string genres;
        // Opening csv file
        ifstream genresFile("/home/mario/Escritorio/fma_metadata/genres.csv");
        // Reading csv file
        if (genresFile.is_open()) {
            while (getline(genresFile, genres, ',')) {
                libs->add(genres);
            }
            genresFile.close();
        }
        // If the csv File is not open.
        else cout << "Unable to open file";


        int index = 1;
        // Creating a new layout for the library scroll area
        for (int j=0; j<libs->getLen() ; j++) {
            if (4*index==j){
                // Filling out the song`s name column
                gLabel = new QLabel(libs->get(j-1).data());
                gLabel->setCursor(Qt::PointingHandCursor);
                gLabel->setStyleSheet("background-color: white; border: 1px inset grey; min-height: 30px;");
                libLayout->addWidget(gLabel);
                index ++;
            }
        }
        // Loading the labels to the UI
        ui->scrollAreaContents->setLayout(libLayout);
    }
    else{
        //If the library is not empty, the layout is iterated looking for the clicked widged in it
        for (int i = 0; i < libLayout->count(); ++i){

            QWidget *widget = libLayout->itemAt(i)->widget();

            // If the layout structure is not empty
            if (widget != NULL){

                // Check if the mouse position is on a label
                if (X>=widget->x()+10 && X <= widget->x()+widget->width()+10
                        && Y>=widget->y()+30 && Y <= widget->y()+widget->height()+30 && Y<530){
                    this->loadSongs();
                }
            }
        }
    }
}

