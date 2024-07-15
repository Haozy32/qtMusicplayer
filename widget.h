#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QUrl>
#include<QDebug>
#include<QDir>
#include<QMediaPlayer>
#include<QAudioOutput>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_file_clicked();

    void setSliderValue();

    void on_play_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_verticalSlider_sliderMoved(int position);

    void on_last_clicked();

    void on_next_clicked();


private:
    Ui::Widget *ui;
    QList<QUrl>playlist;
    QMediaPlayer *m_pMediaPlayer ;
    QTimer *timer;
    QString m_playPath;
    int playRow;
};
#endif // WIDGET_H
