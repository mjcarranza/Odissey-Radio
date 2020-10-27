
#include "odisseyradioplayer.h"
#include "ui_odisseyradioplayer.h"
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <sstream>
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
    ui->setupUi(this);

    // assigning the pointer value to a MediaPlayer instance
    mMediaPlayer = new QMediaPlayer(this);

    connect(mMediaPlayer, &QMediaPlayer::positionChanged, [&](qint64 pos) {
    ui->SongProgress->setValue(pos);
    });

    connect(mMediaPlayer, &QMediaPlayer::durationChanged, [&] (qint64 duration){
    ui->SongProgress->setMaximum(duration);
    });

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

void OdisseyRadioPlayer::on_PlayPauseBtn_clicked()
{
    if (ui->PlayPauseBtn->text() == "Play") {
        mMediaPlayer->play();
        ui->PlayPauseBtn->setText("Pause");
    }
    else {
        mMediaPlayer->pause();
        ui->PlayPauseBtn->setText("Play");
    }
}

void OdisseyRadioPlayer::on_AbrirBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Abrir");
    if (filename.isEmpty()) {
        return;
    }
    mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    mMediaPlayer->setVolume(ui->VolumeSlider->value());
    ui->SongNameLabel->setText(filename);
}

void OdisseyRadioPlayer::on_VolumeSlider_valueChanged(int value)
{
    mMediaPlayer->setVolume(value);
}
