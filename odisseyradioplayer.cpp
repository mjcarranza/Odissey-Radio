#include "odisseyradioplayer.h"
#include "ui_odisseyradioplayer.h"

OdisseyRadioPlayer::OdisseyRadioPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OdisseyRadioPlayer)
{
    ui->setupUi(this);
}

OdisseyRadioPlayer::~OdisseyRadioPlayer()
{
    delete ui;
}

