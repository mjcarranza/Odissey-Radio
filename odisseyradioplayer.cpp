#include "odisseyradioplayer.h"
#include "ui_odisseyradioplayer.h"
//#include <QVBoxLayout>
#include "QMessageBox"
#include <QMediaPlayer>
#include <QFileDialog>
#include <QString>
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
//QVBoxLayout *libLayout = new QVBoxLayout();
auto *lines = new MyLinkedList<string>;
auto *CSVLineList = new MyLinkedList<string>;
string Artists[999999];
int pageCounter = 0;
/**
 * @brief widget method for the core functionalities of the Qt5 application widget.
 * @param parent pointer to the parent container for all the functionalities, containers, slots and methods.
 * @author mjcarranza
 */
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
        QPushButton *artistBtn = new QPushButton();
        string genres;
        string name = getenv("USERNAME");
        // Opening csv file
        ifstream genresFile("/home/" + name + "/fma_metadata/artists.csv");
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
            artistBtn  = new QPushButton(libs->get(j).data());
            artistBtn ->setCursor(Qt::PointingHandCursor);
            artistBtn ->setStyleSheet("min-height: 30px; text-align:left;");
            // Loading the labels to the UI
            ui->listWidget->addItem(libs->get(j).data());
            //QString g= ui->listWidget->currentItem()->text();
            Artists[j-1] = libs->get(j).data();
        }
    }
    ui->MemoryProgressBar->setValue(this->getMemoryValue());
}

/**
 * @brief default generated destructor for the application
 * @author mjcarranza
 */
OdisseyRadioPlayer::~OdisseyRadioPlayer()
{
    delete ui;
}
/**
 * @brief slot method that is summoned when the 'play' button is clicked on the GUI.
 * @author mjcarranza
 */
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

/**
 * @brief slot method that is summoned when the 'Volume' slider value is modified by the user on the GUI.
 * @param value the resulting value between 0-100 on the volume slider.
 * @author AleQuesada2012
 */
void OdisseyRadioPlayer::on_VolumeSlider_valueChanged(int value)
{
    mMediaPlayer->setVolume(value);
}

/**
 * @brief OdisseyRadioPlayer::on_SongProgress_valueChanged changes the song progress to the position selected by User
 * @author AleQuesada2012
 */
void OdisseyRadioPlayer::on_SongProgress_valueChanged(int value)
{
    mMediaPlayer->setPosition(value);
    // ui->SongProgress->setValue(value);
}

/**
 * button that toggles the pagination functionality.
 * @author mjcarranza
 */
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

/**
 * @brief auxiliary method to read the memory usage from the system.
 * @param line a char pointer
 * @return integer i positional value
 * @author mjcarranza
 */
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

/**
 * @brief main memory value obtaining method.
 * @return used memory value in KB.
 * @author mjcarranza
 */
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

/**
 * @brief slot method that loads the songs from the dataset to memory.
 * @author mjcarranza
 */
void OdisseyRadioPlayer::on_LoadLibraryBtn_clicked()
{
    QListWidgetItem *itm = ui->listWidget->currentItem();
    QString artist = itm->text();
    string artText = artist.toUtf8().constData();
    int numrow = ui->SongTable->rowCount(), count =1;
    // If the Library is empty -> fill it out.
    if(ui->SongTable->rowCount() > 0){
        cout<<"entra a limpiar la tabla"<<endl;
        ui->SongTable->setRowCount(0);
    }
    if (ui->SongTable->rowCount() == 0){
        string art;
        string name;
        name = getenv("USERNAME");
        // Opening csv file
        ifstream artistFile("/home/" + name + "/fma_metadata/Tracks_test2.csv");
        delete CSVLineList;
        CSVLineList = new MyLinkedList<string>;
        if (CSVLineList->getLen() == 0){
            if (artistFile.is_open()) {
                while (getline(artistFile, art, ',')) {
                    CSVLineList->add(art);
                }
                artistFile.close();
            }
            // If the csv File is not open.
            else cout << "Unable to open file";
        }

        // Loading song data to the UI
        for (int i=0; i<CSVLineList->getLen() ; i++) {
            if(artText == "All songs"){
                ui->MemoryProgressBar->setValue(this->getMemoryValue());

                // Filling out the song`s name column
                QString InsertingData1 = CSVLineList->get(i).data();
                cout<<CSVLineList->get(i).data()<<endl;
                ui->SongTable->insertRow(ui->SongTable->rowCount()); // Add row
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,0, new QTableWidgetItem(InsertingData1)); // Add data

                // Filling out the song`s artist column
                QString InsertingData2 = CSVLineList->get(i).data();
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,1, new QTableWidgetItem(InsertingData2)); // Add data

                // Filling out the song`s lenght column
                QString InsertingData3 = CSVLineList->get(i-1).data();
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,2, new QTableWidgetItem(InsertingData3)); // Add data

                // Filling out the song`s genre column
                QString InsertingData4 = CSVLineList->get(i+2).data();
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,3, new QTableWidgetItem(InsertingData4)); // Add data

                count ++;
            }
            else if(artText == CSVLineList->get(i).data()){
                ui->MemoryProgressBar->setValue(this->getMemoryValue());

                // Filling out the song`s name column
                QString InsertingData1 = CSVLineList->get(i+1).data();
                cout<<CSVLineList->get(i).data()<<endl;
                ui->SongTable->insertRow(ui->SongTable->rowCount()); // Add row
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,0, new QTableWidgetItem(InsertingData1)); // Add data

                // Filling out the song`s artist column
                QString InsertingData2 = CSVLineList->get(i).data();
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,1, new QTableWidgetItem(InsertingData2)); // Add data

                // Filling out the song`s lenght column
                QString InsertingData3 = CSVLineList->get(i-1).data();
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,2, new QTableWidgetItem(InsertingData3)); // Add data

                // Filling out the song`s genre column
                QString InsertingData4 = CSVLineList->get(i+2).data();
                ui->SongTable->setItem(ui->SongTable->rowCount()-2,3, new QTableWidgetItem(InsertingData4)); // Add data

                count ++;
            }
            // END IF
        } // END FOR
        cout << ui->SongTable->rowCount() << endl;
        if(ui->SongTable->rowCount() == 0) {
            QMessageBox::information(this,"Alert","No songs found for the selected artist.");
          }
    } // END IF

}
/**
 * @brief slot method summoned when the 'show info' button is clicked on the GUI.
 * @author mjcarranza
 */
void OdisseyRadioPlayer::on_InfoBtn_clicked()
{
    QString sngName = ui->SongNameLabel->text();
    string SongName = sngName.toUtf8().constData();
    string art, message;

    for (int i=0; i<CSVLineList->getLen() ; i++) {
        ui->MemoryProgressBar->setValue(this->getMemoryValue());
        string proof = CSVLineList->get(i).data();
        if(CSVLineList->get(i).data() == SongName){
            // Creating the text with current song`s information.
            string data = "Name: \t \t";
            data.append(CSVLineList->get(i).data());
            data.append("\n ");
            data.append("Artist: \t \t");
            data.append(CSVLineList->get(i-1).data());
            data.append("\n ");
            data.append("Lenght: \t \t");
            data.append(CSVLineList->get(i-2).data());
            data.append("\n ");
            data.append("Genre: \t \t");
            data.append(CSVLineList->get(i+1).data());
            data.append("\n ");
            data.append("Track day created:         ");
            data.append(CSVLineList->get(i-3).data());
            data.append("\n ");
            data.append("Album name: \t");
            data.append(CSVLineList->get(i-4).data());
            char temp[data.length()];
            int size = data.length();
            // Adding all data to a sigle variable
            for(int t=0; t<size; t++){
                temp[t]=data.at(t);
            }
            QMessageBox::information(this,tr("SONG INFORMATION"),tr(temp));
            break;
        } // END IF
    } // END FOR
}
/**
 * @brief helper method to find the corresponding folder to a song in the FMA dataset.
 * @param songId the parameter found in a CSV line corresponding to the song numeric ID.
 * @return 3-element string equivalent to the folder name containing the desired song.
 * @author AleQuesada2012
 */
string getIdModifier(string songId) {
  string modifiedId = "000";
  if (songId.length() == 3) {
      // dont change anything, folder is 000
    }
  else if (songId.length() == 4) {
      modifiedId = "00" + songId.substr(0,1);
    }
  else if (songId.length() == 5) {
      modifiedId = "0" + songId .substr(0,2);
    }
  return modifiedId;
}
/**
 * @brief helper method to find the corresponding path of a song in the FMA dataset.
 * @param songId the parameter found in the CSV corresponding to the song's ID.
 * @return 6-element string equivalent to the song's unique name, followed by '.mp3' file type terminology.
 * @author AleQuesada2012
 */
string getIdForPath(string songId) {
  string songPath = "0";
  while (songPath.length() != 6) {
      string tempString = songPath + songId;
      if (tempString.length() == 6) {
          songPath = tempString;
        }
      else {
          songPath.append("0");
        }
    }
  songPath.append(".mp3");
  return songPath;
}
/**
 * @brief slot method summoned when a song element is clicked on the table displayed in the GUI.
 * @param row integer counter for the row in the table view
 * @param column integer counter for the column in the table view
 * @author AleQuesada2012
 */
void OdisseyRadioPlayer::on_SongTable_cellClicked(int row, int column)
{
    ui->SongTable->selectRow(row);
    QString selectedItem = ui->SongTable->currentItem()->text();
    ui->SongNameLabel->setText(selectedItem);
    string songName = selectedItem.toUtf8().constData();
    string user = getenv("USERNAME");
    string numID; // original space with the numeric Id
    string numId; // modified string containing only the numbers for the song id
    for (int i = 0;i < CSVLineList->getLen() ;i++) {
        if (CSVLineList->get(i) == songName) {
            // get the numeric ID of a song using substrings from the data of a list node
            numID = CSVLineList->get(i-5).data();
            int pos = numID.find("\n");
            numId = numID.substr(pos + 1);
            cout << "song ID: " << numId << endl;
            break;
          }
      }
    string folder = getIdModifier(numId);
    cout << "folder is: " << folder << endl;
    string songFileId = getIdForPath(numId);
    cout << "song in file is: " << songFileId << endl;
    string path = "/home/" + user + "/fma_small/" + folder +"/" + songFileId;
    cout << "entire path is: " << path << endl;

    QString filename = QString::fromStdString(path);

    try {
      mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
      mMediaPlayer->setVolume(ui->VolumeSlider->value());
    }  catch (int e) {
      QMessageBox::information(this,"Alert","This song was not found in the dataset, please select another song.");
    }

}
