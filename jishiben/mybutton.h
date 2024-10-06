#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>

class MyButton : public QWidget
{
    Q_OBJECT
private:
    QPixmap pic;//创建成员变量pic
public:
    explicit MyButton(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;//重写事件函数
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event)override;
    void paintEvent(QPaintEvent *event)override;
signals:
    void clickedStore();
};

#endif // MYBUTTON_H
