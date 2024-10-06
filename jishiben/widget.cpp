#include "widget.h"
#include "ui_widget.h"
#include <mybutton.h>
#include <mybuttonopen.h>
#include <iostream>
#include <qfile.h>
#include <string>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>
#include <QCloseEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);

    ui->textEdit->installEventFilter(this);//注册过滤器

    //将自定义按键连接
    connect(ui->mybtn,&MyButton::clickedStore,this,&Widget::on_B_Store_clicked);//连接到on_B_Store_clicked按键处理槽
    connect(ui->mybtn_2,&MyButtonOpen::clickedOpen,this,&Widget::on_B_Open_clicked);

    //连接comboBox多选栏，在label同步显示编码格式
    defaultFontSize = ui->textEdit->font().pointSize();
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBox_currentIndexChanged(int)));
    //连接光标移动，触发高亮显示
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(onCursorPositonChanged()));
    //实现快捷键
    QShortcut *shortcutOpen1 = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")),this);//绑定快捷键
    QShortcut *shortcutSave1 = new QShortcut(QKeySequence(tr("Ctrl+s", "File|Open")),this);
    this->shortcutOpen = shortcutOpen1;//将局部变量赋值给成员变量
    this->shortcutSave = shortcutSave1;
    connect(shortcutOpen,&QShortcut::activated,this,[this](){//当使用 lambda 表达式连接信号和槽时，应该将包含对象（通常是 this）作为第三个参数传递给 connect 函数。
        on_B_Open_clicked();//这确保了 lambda 表达式中使用的任何成员变量或成员函数都是从正确的上下文中调用的。
    });//捕获 this 而不是 [=] 主要是为了确保 lambda 表达式能够安全地访问和操作其所属对象的成员，同时避免悬挂引用和提高性能。
    connect(shortcutSave,&QShortcut::activated,this,[this](){//此外，捕获 this 也使得代码的意图更加明确，有助于代码的阅读和维护。
        on_B_Store_clicked();
    });
    //按键实现放大缩小字体
    QShortcut *shortcutFondUp1 = new QShortcut(QKeySequence(Qt::CTRL|Qt::Key_Equal),this);//绑定按键ctrl + =(+)
    QShortcut *shortcutFondDown1 = new QShortcut(QKeySequence(Qt::CTRL|Qt::Key_Minus),this);//绑定按键ctrl + -
    QShortcut *shortcutFondDefault1 = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_0), this);//绑定按键ctrl + 0
    this->shortcutFondUp = shortcutFondUp1;//将局部变量赋值给成员变量，防止内存泄漏
    this->shortcutFondDown = shortcutFondDown1;
    this->shortcutFondDefault = shortcutFondDefault1;
    connect(shortcutFondUp,&QShortcut::activated,this,&Widget::onFondUp);//绑定槽函数
    connect(shortcutFondDown,&QShortcut::activated,this,&Widget::onFondDown);
    connect(shortcutFondDefault,&QShortcut::activated,this,&Widget::onFondDefault);
    //滚轮实现放大缩小字体

}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)//关闭窗口询问事件
{
    int ret = QMessageBox::warning(this,tr("提示"),tr("您要关闭记事本吗？"),QMessageBox::Ok|QMessageBox::No);
    qDebug()<<ret;
    switch (ret) {
    case QMessageBox::Ok:
        event->accept();
        break;
    case QMessageBox::No:
        event->ignore();
        break;
    }
}

bool Widget::eventFilter(QObject *watched, QEvent *event)//过滤器
{
    if(event->type()== QEvent::Wheel){//如果事件类型是滚轮事件
        if(QApplication::keyboardModifiers()==Qt::ControlModifier){//同时按下ctrl
        QWheelEvent *wEvent = static_cast<QWheelEvent*>(event);//将QEvent对象转为QWheelEvent对象
        qDebug()<<"wheel move2";
                if(wEvent->angleDelta().y()>0){
                    onFondUp();
                }else if(wEvent->angleDelta().y()<0){
                    onFondDown();
                }
                return true;
        }
 }
    return QObject::eventFilter(watched, event);
}

// void Widget::on_B_Open_clicked()//打开
// {
//     QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"/home",tr("Text Files (*.txt)"));//获取要打开的文件名
//     ui->textEdit->clear();//每次打开新文件，清空文本框。
//     file.setFileName(filename);//根据文件名打开文件
//     if(!file.open(QIODeviceBase::ReadWrite|QIODeviceBase::Text)){
//         qDebug()<<"open err";
//         return ;
//     }//打开失败则报错
//     this->setWindowTitle(filename+"-记事本");
//     QTextStream in(&file);//创建文件输出流
//     if(encode=="Utf-8"){
//         in.setEncoding(QStringConverter::Utf8);//设置编码格式
//     }else{
//         in.setEncoding(QStringConverter::System);
//     }//设置编码格式
//     while(!in.atEnd()){//while循环，每次输出一行到字符串note，直到文件内没有数据
//         QString note = in.readLine();
//         ui->textEdit->append(note);//每次将一行字符串note添加进文本框
//     }
//     qDebug()<<file.fileName();
// }

void Widget::on_B_Open_clicked()//打开
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"/home",tr("Text Files (*.txt)"));//获取要打开的文件名
    ui->textEdit->clear();//每次打开新文件，清空文本框。
    file.setFileName(filename);//根据文件名打开文件
    if(!file.open(QIODeviceBase::ReadWrite|QIODeviceBase::Text)){
        qDebug()<<"open err";
        return ;
    }//打开失败则报错
    this->setWindowTitle(filename+"-记事本");
    QTextStream in(&file);//创建文件输出流
    if(encode=="Utf-8"){
        in.setEncoding(QStringConverter::Utf8);//设置编码格式
    }else{
        in.setEncoding(QStringConverter::System);
    }//设置编码格式
    while(!in.atEnd()){//while循环，每次输出一行到字符串note，直到文件内没有数据
        QString note = in.readLine();
        ui->textEdit->append(note);//每次将一行字符串note添加进文本框
    }
    qDebug()<<file.fileName();
}

void Widget::on_B_Store_clicked()//保存
{
    if(!file.isOpen()){//如果文件已经打开的话就不用选择文件了
        QString filename = QFileDialog::getSaveFileName(this,tr("Save File"),"F:/Qt_code",tr("Text Files (*.txt,*.doc,*.docx)"));//获取要保存的文件名
        file.setFileName(filename);//根据文件名打开文件
        if(!file.open(QIODeviceBase::ReadWrite|QIODeviceBase::Text)){
            qDebug()<<"Open err";
            return ;
        }//打开失败的话报错
    }
    file.resize(0);//每次保存都要把之前的旧文件清除
    QString text = ui->textEdit->toPlainText();//将文本框中的文字写入字符串text中
    QTextStream out(&file);//创造文件输入流
    if(encode=="Utf-8"){
        out.setEncoding(QStringConverter::Utf8);//设置编码格式
    }else{
        out.setEncoding(QStringConverter::System);
    }
    qDebug()<<ui->comboBox->currentText();
    out<<text;//输入数据到文件
    qDebug()<<file.fileName();
}


void Widget::on_B_Close_clicked()//关闭文件，清空文本框。
{
    QMessageBox qMessageBox;
    qMessageBox.setWindowTitle("提示");
    qMessageBox.setText("您是否要关闭该文件？");
    qMessageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    QMessageBox::StandardButton buttonClick = static_cast<QMessageBox::StandardButton>(qMessageBox.exec());//static_cast<QMessageBox::StandardButton>转换城StandardButton形式
    if(buttonClick==QMessageBox::Ok){
        qDebug()<<file.fileName();
        ui->textEdit->clear();//清空文本框
        if(file.isOpen()){//如果文件是打开的
            file.close();//关闭文件
            if(!file.isOpen()){//判断是否关闭成功，成功则输出提示
                qDebug()<<"this file has been closed";
            }
            this->setWindowTitle("记事本");
        }
    }
}



void Widget::on_comboBox_currentIndexChanged(int index)//选择编码格式
{
    encode = ui->comboBox->currentText();
    ui->textEdit->clear();
    file.seek(0);//将光标重置
    if(file.isOpen()){
        QTextStream in(&file);//创建文件输出流
        if(encode=="Utf-8"){
            in.setEncoding(QStringConverter::Utf8);//设置编码格式
        }else{
            in.setEncoding(QStringConverter::System);
        }//设置编码格式
        while(!in.atEnd()){//while循环，每次输出一行到字符串note，直到文件内没有数据
            QString note = in.readLine();
            ui->textEdit->append(note);//每次将一行字符串note添加进文本框
        }
    }
    ui->T_code->setText(encode);//在label显示编码格式
}

void Widget::onCursorPositonChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();//获取光标对象

    int row = cursor.blockNumber()+1,col = cursor.columnNumber()+1;//获取光标的位置
    QString code = "第"+QString::number(row)+"行,第"+QString::number(col)+"列";//将整型数光标位置改为QString类型
    ui->T_position->setText(code);//在label光标位置
    // qDebug()<<code;

    //文本行高亮显示
    QList<QTextEdit::ExtraSelection> extraselections;//ExtraSelection 是 QTextEdit 的一个类，用于定义额外的文本选择或者高亮区域。
    QTextEdit::ExtraSelection ext;//它允许你对文本编辑器中的某些部分进行自定义的格式化，比如高亮显示、设置背景色或者改变边框等。

    ext.cursor = ui->textEdit->textCursor();//找到光标所在位置
    QBrush qb(Qt::gray);//设置背景涂刷
    ext.format.setBackground(qb);//设置背景色
    ext.format.setForeground(Qt::white);//设置文字颜色
    ext.format.setProperty(QTextFormat::FullWidthSelection,true);//高亮显示一整行
    extraselections.append(ext);//将ext添加进Es链表
    ui->textEdit->setExtraSelections(extraselections);//应用到文本框
}

void Widget::onFondUp()//放大slot
{
    qDebug()<<"up";
    int currentFondSzie = ui->textEdit->currentFont().pointSize();//获取当前文本框内的字体大小
    if(currentFondSzie <= 50){//限定最大字体大小不超过50
        currentFondSzie+=1;//每次将字体大小+1
        ui->textEdit->setFont(QFont(ui->textEdit->font().family(),currentFondSzie));//设置文本框字体和大小
    }
}

void Widget::onFondDown()//缩小slot
{
    qDebug()<<"down";
    int currentFondSzie = ui->textEdit->currentFont().pointSize();
    if(currentFondSzie >= 1){
        currentFondSzie-=1;
        ui->textEdit->setFont(QFont(ui->textEdit->font().family(),currentFondSzie));
    }
}

void Widget::onFondDefault()//恢复默认slot
{
    qDebug()<<"defalut";
    int currentFondSzie = ui->textEdit->currentFont().pointSize();
    if(currentFondSzie != defaultFontSize){
        ui->textEdit->setFont(QFont(ui->textEdit->font().family(),defaultFontSize));
    }
}

// void Widget::wheelEvent(QWheelEvent *event)//鼠标滚轮事件
// {
//     qDebug()<<"wheel move";
//     if(event->modifiers() & Qt::ControlModifier){//如果CTRL和滚轮一同按下
//         if(event->angleDelta().y()>0){//向上滚动，event->angleDelta().y()的值会大于0
//             onFondUp();//执行字体放大槽函数
//         }else if(event->angleDelta().y()<0){//向下滚动，event->angleDelta().y()的值会小于0
//             onFondDown();//执行字体缩小槽函数
//         }
//         event->accept();//接受该事件，防止继续传播
//     }
// }
