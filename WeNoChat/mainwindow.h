#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QListWidgetItem>
#include <QMainWindow>
#include <chatmessagewidget.h>
#include <QDateTime>
#include "communicate_utils.h"
#include "searchfriends.h"
#include "friendlist.h"
#include <QImage>
#include "messagerecord.h"
#include "wncimage.h"
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QString ud, QTcpSocket *sock, QWidget *parent = 0);
    ~MainWindow();
    void pushImageIntoChatWindow(bool type, QImage msg, QString time, QImage *image = NULL, bool isSending = false);
    void dealImage(ChatMessageWidget *messageW, QListWidgetItem *item, QImage img, QString time, ChatMessageWidget::User_Type type, QImage *image);
    int packData(const QString &pack,Json::Value &data);
    void changeMyIcon(QImage * uimg);
protected:
    void mouseMoveEvent(QMouseEvent *ev);  //鼠标移动
    void mousePressEvent(QMouseEvent *ev); //鼠标按下移动
    void mouseReleaseEvent(QMouseEvent *ev);
private slots:
    void on_closeButton_clicked();

    void on_hideButton_clicked();

    void on_pushButton_addfriend_clicked();
    void on_send_clicked();
    void hadreadyread();

    void pushMessageIntoChatWindow(bool type, QString msg, QString time, QImage *image = NULL, bool isSending = false);
    void clearAllMessage();
    void dealMessageTime(QString curMsgTime);
    void dealMessage(ChatMessageWidget *messageW, QListWidgetItem *item, QString text, QString time, ChatMessageWidget::User_Type type, QImage *image = NULL);

    void startChatting(QVariant variant);
    void deleteFriend(QVariant variant);
    void on_pushButton_image_clicked();
    void on_pushButton_send_image_clicked();
    void on_biaoqingButton_clicked();

    void on_bButton1_clicked();
    void on_bButton2_clicked();
    void on_bButton3_clicked();
    void on_bButton4_clicked();
    void on_bButton5_clicked();
    void on_bButton6_clicked();
    void on_bButton7_clicked();
    void on_bButton8_clicked();
    void on_bButton9_clicked();


private:
    struct ChatInfo
    {
        Ui::User chatFriend;
        MessageRecord *record;
    };

    Ui::MainWindow *ui;
    QTcpSocket *client;
    QString udata;
    QImage user_image;
    searchFriends *add;
    std::vector<Ui::User> userList;

    Ui::FriendList *friendList;
    ChatInfo chattingInfo;
    void initConnection();
    WNCimage *imag;
    QString tmpCmd;
    QPoint p;
};

#endif // MAINWINDOW_H
