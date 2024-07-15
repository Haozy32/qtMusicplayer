#include "widget.h"
#include "ui_widget.h"
#include<QFileDialog>
#include<QDebug>
#include<QDir>
#include<QMediaPlayer>
#include<QAudioOutput>
#include<QUrl>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer=new QTimer;
    timer->setInterval(1000);
    timer->start();
m_pMediaPlayer = new QMediaPlayer(this);
    //m_pMediaPlayer->setMedia(QUrl::fromLocalFile("D:\\code\\qt\\musicplayer\\assers\\music\\因为爱情.mp3"));
    //m_pMediaPlayer->play();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_file_clicked()
{
   QString path= QFileDialog::getExistingDirectory(this,"请选择你的文件夹","D:\\code\\qt\\musicplayer\\assers\\music");
   qInfo()<<path;
   QDir dir(path);
   auto p=dir.entryList(QStringList()<<"*.mp3");
   qInfo()<<p;
   ui->listWidget->addItems(p);
   ui->listWidget->setCurrentRow(0);
   for(auto file:p)
       playlist.append(QUrl::fromLocalFile(path+"/"+file));
   qInfo()<<playlist;
}


void Widget::on_play_clicked()
{
    switch (m_pMediaPlayer->state()) {
    case QMediaPlayer::State::StoppedState:{
        playRow=ui->listWidget->currentRow();
        m_pMediaPlayer->setMedia(playlist[playRow]);
        m_pMediaPlayer->play();
        connect(timer, SIGNAL(timeout()), this, SLOT(setSliderValue()));
        break;}
    case QMediaPlayer::State::PlayingState:{
        m_pMediaPlayer->pause();
        break;}
    case QMediaPlayer::State::PausedState:{
        m_pMediaPlayer->play();
        break;}
    }
}


void Widget::on_horizontalSlider_sliderMoved(int position)
{
    m_pMediaPlayer->setPosition(m_pMediaPlayer->duration()*position/100);
}

void Widget::setSliderValue()
{
    ui->horizontalSlider->setValue(m_pMediaPlayer->position()*100/m_pMediaPlayer->duration());
}

void Widget::on_verticalSlider_sliderMoved(int position)
{
    m_pMediaPlayer->setVolume(position);
}

void Widget::on_next_clicked()
{
    playRow=(playRow+1)%playlist.size();
    ui->listWidget->setCurrentRow(playRow);
    m_pMediaPlayer->setMedia(playlist[playRow]);
    m_pMediaPlayer->play();
}

void Widget::on_last_clicked()
{
    playRow=(playRow-1)%playlist.size();
    ui->listWidget->setCurrentRow(playRow);
    m_pMediaPlayer->setMedia(playlist[playRow]);
    m_pMediaPlayer->play();
}

