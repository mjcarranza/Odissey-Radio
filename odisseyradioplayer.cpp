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
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

using namespace std;
auto *libs = new MyLinkedList<string>;
QVBoxLayout *libLayout = new QVBoxLayout();
auto *lines = new MyLinkedList<string>;
auto *artistList = new MyLinkedList<string>;
string Artists[999999];
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

    // If the Library is empty -> fill it out.
    if(libs->getLen()==0){
        QLabel *gLabel = new QLabel();
        string genres;
        // Opening csv file
        ifstream genresFile("/home/mario/Escritorio/fma_metadata/artists.csv");
        // Reading csv file
        if (genresFile.is_open()) {
            while (getline(genresFile, genres)) {
                libs->add(genres);
            }
            genresFile.close();
        }
        // If the csv File is not open.
        else cout << "Unable to open file";

        // Creating a new layout for the library scroll area
        for (int j=1; j<libs->getLen() ; j++) {
            // Filling out the song`s name column
            gLabel = new QLabel(libs->get(j).data());
            gLabel->setCursor(Qt::PointingHandCursor);
            gLabel->setStyleSheet("background-color: white; border: 1px inset grey; min-height: 30px;");
            libLayout->addWidget(gLabel);
            Artists[j-1] = libs->get(j).data();
            string r = libs->get(j).data();
        }
        // Loading the labels to the UI
        ui->scrollAreaWidgetContents->setLayout(libLayout);
    }
    ui->MemoryProgressBar->setValue(this->getMemoryValue());
}

OdisseyRadioPlayer::~OdisseyRadioPlayer()
{
    delete ui;
}

void OdisseyRadioPlayer::mousePressEvent(QMouseEvent *ev)
{
    // Cursor positions
    int X = ev->x();
    int Y = ev->y();
    int space = 54;
    int numRow = ui->SongTable->rowCount();
    cout<<ui->SongTable->rowCount();
    ui->MemoryProgressBar->setValue(this->getMemoryValue());

    // If the Library is empty -> fill it out.
    if(ui->SongTable->rowCount() > 0){
        cout<<"entra a limpiar la tabla"<<endl;
        for ( int i = numRow; i>=0 ; i-- )
        {
            ui->SongTable->removeRow(i);
        }
    }
    if (ui->SongTable->rowCount() == 0){
        //If the library is not empty, the layout is iterated looking for the clicked widged in it
        for (int i = 0; i < libLayout->count(); ++i){
            ui->MemoryProgressBar->setValue(this->getMemoryValue());
            // Obtains the widget in the i position in libLayout
            QWidget *widget = libLayout->itemAt(i)->widget();

            // If the obtained widget is not null
            if (widget != NULL){

                // Check if the mouse`s position is on the label
                if (X >= widget->x()+10 && X <= widget->x()+widget->width()+10
                        && Y >= widget->y()+30 && Y <= widget->y()+widget->height()+30 && Y<530){
                    // Look for the selected artist

                    for (int i=1;i <= libs->getLen() ;i++ ) {
                        ui->MemoryProgressBar->setValue(this->getMemoryValue());
                        string selectedArtist = Artists[i-1];

                        if (widget->y()+30 <= space*i && widget->y()+ 30 + widget->height() >= space*i ){
                            cout<<widget->y()<<endl;
                            cout<<i<<endl;
                            // Look for the artist`s asociated songs
                            string art;
                            // Opening csv file
                            ifstream artistFile("/home/mario/Escritorio/fma_metadata/Tracks_test2.csv");
                            // Reading csv file
                            if (artistList->getLen() == 0){
                                if (artistFile.is_open()) {
                                    while (getline(artistFile, art, ',')) {
                                        artistList->add(art);
                                    }
                                    artistFile.close();
                                }
                                // If the csv File is not open.
                                else cout << "Unable to open file";
                            }

                            // Loading song data to the UI
                            for (int i=0; i<artistList->getLen() ; i++) {
                                ui->MemoryProgressBar->setValue(this->getMemoryValue());
                                //cout << artistList->get(i).data()<<endl;;
                                string proof = artistList->get(i).data();
                                if (selectedArtist == artistList->get(i).data()){
                                    // Filling out the song`s name column
                                    QString InsertingData1 = artistList->get(i+1).data();
                                    ui->SongTable->insertRow(ui->SongTable->rowCount()); // Add row
                                    ui->SongTable->setItem(ui->SongTable->rowCount()-2,0, new QTableWidgetItem(InsertingData1)); // Add data

                                    // Filling out the song`s lenght column
                                    QString InsertingData2 = artistList->get(i).data();
                                    ui->SongTable->setItem(ui->SongTable->rowCount()-2,1, new QTableWidgetItem(InsertingData2)); // Add data

                                    // Filling out the song`s artist column
                                    QString InsertingData3 = artistList->get(i-1).data();
                                    ui->SongTable->setItem(ui->SongTable->rowCount()-2,2, new QTableWidgetItem(InsertingData3)); // Add data

                                    // Filling out the song`s genre column
                                    QString InsertingData4 = artistList->get(i-2).data();
                                    ui->SongTable->setItem(ui->SongTable->rowCount()-2,3, new QTableWidgetItem(InsertingData4)); // Add data

                                } // END IF
                            } // END FOR
                        }// END IF
                    }// END FOR
                }// END IF
            }// END IF
        }// END FOR
    }
    ui->MemoryProgressBar->setValue(this->getMemoryValue());
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

// Button to enable or disable pagination
void OdisseyRadioPlayer::on_PaginationBtn_clicked()
{
    // if the box is checked, it enables pagination
    if (ui->PaginationCheckBx->isChecked()){
        ui->PaginationBtn->setStyleSheet("background-color: green;");
        // call method to activate pagination
        // Pagination method required !!!!
    }
    // if the box is not checked, it disables pagination
    else{
        ui->PaginationBtn->setStyleSheet("background-color: grey;");
        // call method to disable pagination
        // Pagination method required!!!!
    }
}

int OdisseyRadioPlayer::parseLine(char *line)
{
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int OdisseyRadioPlayer::getMemoryValue()
{
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    int totalMemory = 11000;
    int usedMemory;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line)/1000; //Memory usage in MB
            break;
        }
    }
    fclose(file);
    usedMemory = (result * 100) / totalMemory;
    return usedMemory; //this value is in KB!
}
//string strtext = NombreNodo.toUtf8().constData();///////////////////// pasar de qstring a string

// Loads all songs in the dataset
void OdisseyRadioPlayer::on_LoadLibraryBtn_clicked()
{
    int numrow = ui->SongTable->rowCount(), count =1;
    // If the Library is empty -> fill it out.
    if(ui->SongTable->rowCount() > 0){
        cout<<"entra a limpiar la tabla"<<endl;
        for ( int i = numrow; i>=0 ; i-- )
        {
            ui->SongTable->removeRow(i);
        }
    }
    if (ui->SongTable->rowCount() == 0){
        string art;
        // Opening csv file
        ifstream artistFile("/home/mario/Escritorio/fma_metadata/Tracks_test2.csv");
        if (artistList->getLen() == 0){
            if (artistFile.is_open()) {
                while (getline(artistFile, art, ',')) {
                    artistList->add(art);
                }
                artistFile.close();
            }
            // If the csv File is not open.
            else cout << "Unable to open file";
        }
        cout<<artistList->getLen()<<endl;
        // Loading song data to the UI
        for (int i=0; i<artistList->getLen() ; i++) {
            if(i == count*5){
                ui->MemoryProgressBar->setValue(this->getMemoryValue());

                // Filling out the song`s name column
                QString InsertingData1 = artistList->get(i).data();
                cout<<artistList->get(i).data()<<endl;
                ui->SongTable->insertRow(ui->SongTable->rowCount()); // Add row
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,0, new QTableWidgetItem(InsertingData1)); // Add data

                // Filling out the song`s lenght column
                QString InsertingData2 = artistList->get(i-1).data();
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,1, new QTableWidgetItem(InsertingData2)); // Add data

                // Filling out the song`s artist column
                QString InsertingData3 = artistList->get(i-2).data();
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,2, new QTableWidgetItem(InsertingData3)); // Add data

                // Filling out the song`s genre column
                QString InsertingData4 = artistList->get(i-2).data();
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,3, new QTableWidgetItem(InsertingData4)); // Add data

                count ++;
            }

        } // END FOR
    }

}
