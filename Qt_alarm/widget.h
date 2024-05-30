#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLCDNumber>
#include<QTimerEvent>
#include<QTime>
#include<QDebug>
#include <QTextToSpeech>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void timerEvent(QTimerEvent *);
private slots:
    void on_StartBtn_clicked();
    void on_StopBtn_clicked();
private:
    Ui::Widget *ui;
    QLCDNumber *lcd;
    int clickedflag = 0;
    int showflag = 1;
    QString systimetext;
    QString current_color;//颜色
    float Opacity; //透明度控制
    //定义一个播报着
    QTextToSpeech speech;
    QTextToSpeech::State state;
    //鼠标
    int mouse_flag=0;
    int mouse_x;
    int mouse_y;
    //鼠标按下
    void mousePressEvent(QMouseEvent *ev);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *ev);

};
#endif // WIDGET_H
