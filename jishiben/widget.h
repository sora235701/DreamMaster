#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qfile.h>
#include <QShortcut>
#include <QEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QFile file;
    QString encode;
    int defaultFontSize;
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
private slots:
    void on_B_Open_clicked();

    void on_B_Store_clicked();

    void on_B_Close_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void onCursorPositonChanged();

    void onFondUp();

    void onFondDown();

    void onFondDefault();

    // void wheelEvent(QWheelEvent *event) override;
private:
    Ui::widget *ui;
    QShortcut *shortcutOpen;
    QShortcut *shortcutSave;
    QShortcut *shortcutFondUp;
    QShortcut *shortcutFondDown;
    QShortcut *shortcutFondDefault;
};
#endif // WIDGET_H
