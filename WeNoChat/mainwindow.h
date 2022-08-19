#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QListWidgetItem>
#include <QMainWindow>
#include <chatmessagewidget.h>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QString ud,QTcpSocket * sock,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_closeButton_clicked();

    void on_hideButton_clicked();

    void on_send_clicked();

    void hadreadyread();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *client;
    QString udata;
    void pushMessageIntoChatWindow(bool type,QString msg,QString time,bool isSending);
    void dealMessageTime(QString curMsgTime);
    void dealMessage(ChatMessageWidget *messageW, QListWidgetItem *item, QString text, QString time,  ChatMessageWidget::User_Type type);
};

#endif // MAINWINDOW_H
