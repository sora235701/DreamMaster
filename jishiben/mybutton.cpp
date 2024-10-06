#include "mybutton.h"

#include <QPainter>
MyButton::MyButton(QWidget *parent): QWidget{parent}
{
    pic.load(":/arrow-down.svg");//绘制图片
    setFixedSize(pic.size());//设置图片大小
    update();//每次都得更新，更新时执行paintEvent
}

void MyButton::mousePressEvent(QMouseEvent *event)
{
    pic.load(":/arrow-down-circle.svg");
    emit clickedStore();
    update();
}

void MyButton::enterEvent(QEnterEvent *event)
{
    pic.load(":/arrow-down-circle-fill.svg");

    update();
}

void MyButton::leaveEvent(QEvent *event)
{
    pic.load(":/arrow-down.svg");
    update();
}

void MyButton::paintEvent(QPaintEvent *event)
{
    QPainter qPainter(this);//创建一个qPainter
    qPainter.drawPixmap(rect(),pic);//画一个矩形图像
    update();
}

