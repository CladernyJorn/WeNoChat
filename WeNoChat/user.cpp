#include "user.h"
#include "ui_user.h"

user::user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
}

user::user(QTcpSocket *sock,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    client = sock;
    connect(client,SIGNAL(readyRead()),this,SLOT(hadreadyread()));
}
user::~user()
{
    delete ui;
}

void user::hadreadyread()
{
    QByteArray recvArray = client->readAll();
    //如果确认用户存在，跳转至下一个界面
    if(1)
    {
        //从服务端获取密保问题
        QString ques = "1234";
        disconnect(client,SIGNAL(readyRead()),0,0);
        q = new question(ques,client);
        q->show();
        this->close();
    }
    else
    {
        QMessageBox::information(this,"提示","用户不存在");
        return;
    }
}

void user::on_pushButton_clicked()
{
    QString uName = ui->userName->text();
    QString phonenum = ui->phonenumber->text();

    QString packData = uName + phonenum;
    client->write(packData.toLocal8Bit());
}
