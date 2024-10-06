/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mybutton.h>
#include <mybuttonopen.h>

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *B_Widget;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    MyButtonOpen *mybtn_2;
    MyButton *mybtn;
    QPushButton *B_Close;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QTextEdit *textEdit;
    QWidget *Bottom;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *T_position;
    QLabel *T_code;

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName("widget");
        widget->resize(800, 600);
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        B_Widget = new QWidget(widget);
        B_Widget->setObjectName("B_Widget");
        B_Widget->setMinimumSize(QSize(780, 90));
        B_Widget->setBaseSize(QSize(0, 0));
        B_Widget->setStyleSheet(QString::fromUtf8("background-color: rgb(197, 197, 197);"));
        widget1 = new QWidget(B_Widget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(13, 2, 267, 81));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        mybtn_2 = new MyButtonOpen(widget1);
        mybtn_2->setObjectName("mybtn_2");
        mybtn_2->setMinimumSize(QSize(50, 50));
        mybtn_2->setBaseSize(QSize(50, 50));

        horizontalLayout_2->addWidget(mybtn_2);

        mybtn = new MyButton(widget1);
        mybtn->setObjectName("mybtn");
        mybtn->setMinimumSize(QSize(50, 50));
        mybtn->setBaseSize(QSize(50, 50));

        horizontalLayout_2->addWidget(mybtn);

        B_Close = new QPushButton(widget1);
        B_Close->setObjectName("B_Close");

        horizontalLayout_2->addWidget(B_Close);

        comboBox = new QComboBox(widget1);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout_2->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(B_Widget);

        textEdit = new QTextEdit(widget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        Bottom = new QWidget(widget);
        Bottom->setObjectName("Bottom");
        Bottom->setMinimumSize(QSize(0, 50));
        Bottom->setStyleSheet(QString::fromUtf8("background-color: rgb(197, 197, 197);"));
        verticalLayout_3 = new QVBoxLayout(Bottom);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        T_position = new QLabel(Bottom);
        T_position->setObjectName("T_position");

        horizontalLayout->addWidget(T_position);

        T_code = new QLabel(Bottom);
        T_code->setObjectName("T_code");

        horizontalLayout->addWidget(T_code);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout->addWidget(Bottom);


        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QWidget *widget)
    {
        widget->setWindowTitle(QCoreApplication::translate("widget", "Widget", nullptr));
        B_Close->setText(QCoreApplication::translate("widget", "\345\205\263\351\227\255", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("widget", "Utf-8", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("widget", "System", nullptr));

        T_position->setText(QCoreApplication::translate("widget", "\347\254\254x\350\241\214\347\254\254x\345\210\227", nullptr));
        T_code->setText(QCoreApplication::translate("widget", "UTF8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
