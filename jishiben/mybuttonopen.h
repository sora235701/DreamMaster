#ifndef MYBUTTONOPEN_H
#define MYBUTTONOPEN_H

#include <QWidget>

class MyButtonOpen : public QWidget
{
    Q_OBJECT
public:
    explicit MyButtonOpen(QWidget *parent = nullptr);
private:
    QPixmap pic;//创建成员变量pic
    void mousePressEvent(QMouseEvent *event) override;//重写事件函数
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event)override;
    void paintEvent(QPaintEvent *event)override;
signals:
    void clickedOpen();//定义自定义案件的按下信号
signals:
};

#endif // MYBUTTONOPEN_H
