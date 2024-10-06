#include "mybuttonopen.h"
#include <QPainter>
MyButtonOpen::MyButtonOpen(QWidget *parent)
    : QWidget{parent}
{
    pic.load(":/arrow-up.svg");//绘制图片
    setFixedSize(pic.size());//设置图片大小
    update();//每次都得更新，更新时执行paintEvent
}
void MyButtonOpen::mousePressEvent(QMouseEvent *event)
{
    pic.load(":/arrow-up-circle.svg");
    emit clickedOpen();//emtt自定义的按键按下信号
    update();
}

void MyButtonOpen::enterEvent(QEnterEvent *event)
{
    pic.load(":/arrow-up-circle-fill.svg");

    update();
}

void MyButtonOpen::leaveEvent(QEvent *event)
{
    pic.load(":/arrow-up.svg");
    update();
}

void MyButtonOpen::paintEvent(QPaintEvent *event)
{
    QPainter qPainter(this);//创建一个qPainter
    qPainter.drawPixmap(rect(),pic);//画一个矩形图像
    update();
}
