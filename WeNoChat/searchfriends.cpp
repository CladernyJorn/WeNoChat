#include "searchfriends.h"
#include "ui_searchfriends.h"

searchFriends::searchFriends(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchFriends)
{
    ui->setupUi(this);
}

searchFriends::searchFriends(QString u,QTcpSocket * sock,QWidget *parent):
    QDialog(parent),
    ui(new Ui::searchFriends)
{
    ui->setupUi(this);
    client=sock;
    udata=u;
}

searchFriends::~searchFriends()
{
    delete ui;
}

void searchFriends::on_pushButton_clicked()
{
    //获取输入框内容
    QString friend_userName = ui->lineEdit->text();
    //向服务器发送新好友
    std::string data=Encoder_addfriends(udata.toStdString(),friend_userName.toStdString());
    QString packData = QString::fromStdString(data);
    client->write((packData.toLocal8Bit()));
}
