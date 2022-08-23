#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QListWidgetItem>
#include <QMainWindow>
#include <UI/chatmessagewidget.h>
#include <QDateTime>
#include "utils/communicate_utils.h"
#include "searchfriends.h"
#include "friendlist.h"
#include <QImage>
#include "messagerecord.h"
#include "socket/datasock.h"
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QString ud, QWidget *parent = 0);
    ~MainWindow();
    void pushImageIntoChatWindow(bool type, QImage msg, QString time, QImage *image = NULL, bool isSending = false);
    void dealImage(ChatMessageWidget *messageW, QListWidgetItem *item, QImage img, QString time, ChatMessageWidget::User_Type type, QImage *image);
    void changeMyIcon(QImage *uimg);

protected:
    void mouseMoveEvent(QMouseEvent *ev);  //鼠标移动
    void mousePressEvent(QMouseEvent *ev); //鼠标按下移动
    void mouseReleaseEvent(QMouseEvent *ev);
private slots:
    void on_closeButton_clicked();

    void on_hideButton_clicked();

    void on_pushButton_addfriend_clicked();
    void on_send_clicked();

    void pushMessageIntoChatWindow(bool type, QString msg, QString time, QImage *image = NULL, bool isSending = false);
    void clearAllMessage();
    void dealMessageTime(QString curMsgTime);
    void dealMessage(ChatMessageWidget *messageW, QListWidgetItem *item, QString text, QString time, ChatMessageWidget::User_Type type, QImage *image = NULL);

    void startChatting(QVariant variant);

    void on_pushButton_image_clicked();
    void on_pushButton_send_image_clicked();

private:
    struct ChatInfo
    {
        Ui::User chatFriend;
        MessageRecord *record;
    };

    Ui::MainWindow *ui;
    DataSock &client;
    QString udata;
    QImage user_image;
    searchFriends *add;
    std::vector<Ui::User> userList;
    Ui::FriendList *friendList;
    ChatInfo chattingInfo;
    void initConnection();

    std::map <QString, MessageRecord> msgRcd;

    QString tmpCmd;
    QPoint p;

    void _initHandler();
};

#endif // MAINWINDOW_H
