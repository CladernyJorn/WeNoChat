#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QListWidgetItem>
#include <QMainWindow>
#include <chatmessagewidget.h>
#include <QDateTime>
#include"communicate_utils.h"
#include"searchfriends.h"
#include "friendlist.h"
#include <QImage>
#include "messagerecord.h"
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

    void on_pushButton_addfriend_clicked();
    void on_send_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void hadreadyread();

    void pushMessageIntoChatWindow(bool type,QString msg,QString time,QImage* image = NULL,bool isSending = false);
    void clearAllMessage();
    void dealMessageTime(QString curMsgTime);
    void dealMessage(ChatMessageWidget *messageW, QListWidgetItem *item, QString text, QString time,  ChatMessageWidget::User_Type type, QImage* image = NULL);

    void startChatting(QVariant variant);

private:
    struct ChatInfo
    {
        Ui::User chatFriend;
        MessageRecord *record;
    };

    Ui::MainWindow *ui;
    QTcpSocket *client;
    QString udata;
    searchFriends *add;
    std::vector<std::string> userList;
    Ui::FriendList *friendList;
    ChatInfo chattingInfo;
    void initConnection();
};

#endif // MAINWINDOW_H
