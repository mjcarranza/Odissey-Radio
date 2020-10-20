#ifndef ODISSEYRADIOPLAYER_H
#define ODISSEYRADIOPLAYER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class OdisseyRadioPlayer; }
QT_END_NAMESPACE

class OdisseyRadioPlayer : public QMainWindow
{
    Q_OBJECT

public:
    OdisseyRadioPlayer(QWidget *parent = nullptr);
    ~OdisseyRadioPlayer();

private slots:
    void on_PlayPauseBtn_clicked();

private:
    Ui::OdisseyRadioPlayer *ui;
};
#endif // ODISSEYRADIOPLAYER_H
