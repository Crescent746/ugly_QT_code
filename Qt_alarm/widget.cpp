#include "widget.h"
#include "ui_widget.h"
#include <windows.h>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(570,300);
    this->setWindowTitle("电子闹钟");
    ui->TimeEdit->setStyleSheet("border: 1px solid whitle;");
    ui->TimeEdit->resize(250,75);
    ui->TimeEdit->move(300,20);
    ui->StartBtn->resize(80,40);
    ui->StartBtn->move(300,115);
    ui->StopBtn->resize(80,40);
    ui->StopBtn->move(300+ui->StartBtn->width()+20,115);
    ui->StopBtn->setEnabled(false);
    ui->MsgEdit->resize(this->width()-40,90);
    ui->MsgEdit->move(20,this->height()-20-90);
    ui->MsgEdit->setPlaceholderText("请在这里输入提醒消息");
    ui->TimeEdit->setDisplayFormat("HH:mm");
    lcd = new QLCDNumber(this);
    lcd->resize(250,75);
    lcd->move(20,20);
    lcd->setSegmentStyle(QLCDNumber::Flat);
//    // 设置能显示的位数
//    lcd->setDigitCount(20);
    lcd->setStyleSheet("border: 1px solid white; color: #333333; background-color: #BDB76B;");
    //启动定时器
    startTimer(1000);
    //无边框
    setWindowFlags(Qt::FramelessWindowHint);

    Opacity = 0.8; // 透明度设置
    current_color = "background:#EEE8AA"; //当前背景色设置
    this->setStyleSheet(current_color);                 //设置背景颜色
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置为无边框窗口
    this->setWindowOpacity(Opacity);                    //设置不透明度
    // 置顶
    ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    //    // 不置顶
    //    ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);


}
Widget::~Widget()
{
    delete ui;
}
//重写定时器事件
void Widget::timerEvent(QTimerEvent *)
{
    //1.获取系统时间
    QTime systime = QTime::currentTime();
    //2.将系统时间转换为字符串
    systimetext = systime.toString("HH:mm");
    if(clickedflag == 1 )
    {
        if(speech.state()!=1)
        {
            if(ui->TimeEdit->text()==systimetext)
            {
                speech.say(ui->MsgEdit->toPlainText());
            }
        }
    }
    if(showflag)
    {
        systimetext[2] = ':';
        showflag = false;
    }else{
        systimetext[2] = ' ';
        showflag = true;
    }
    //将时间字符串展示到LCD中
    lcd->display(systimetext);
}
void Widget::on_StartBtn_clicked()
{
    clickedflag = 1;
    //开始后禁用输入时间
    ui->TimeEdit->setEnabled(false);
    ui->MsgEdit->setEnabled(false);
    ui->StartBtn->setEnabled(false);
    ui->StopBtn->setEnabled(true);
}
void Widget::on_StopBtn_clicked()
{
    clickedflag = 0;
    ui->TimeEdit->setEnabled(true);
    ui->MsgEdit->setEnabled(true);
    ui->StartBtn->setEnabled(true);
    ui->StopBtn->setEnabled(false);
}
//鼠标按下
void Widget::mousePressEvent(QMouseEvent *ev)
{
    mouse_flag=1;
    mouse_x=ev->x();
    mouse_y=ev->y();
}
//鼠标移动
void Widget::mouseMoveEvent(QMouseEvent *ev)
{
    if(mouse_flag==1)
    {
      int x=this->x()+ev->x();
      int y=this->y()+ev->y();
      //后面两个数字的大小要与窗口大小一致，否则鼠标点击后窗口大小会变
      setGeometry(x-mouse_x,y-mouse_y,600,450);
    }
}
