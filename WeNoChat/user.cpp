#include "user.h"
#include "ui_user.h"
#include<QMouseEvent>

user::user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
}

user::user(QTcpSocket *sock,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    client = sock;
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
    connect(client,SIGNAL(readyRead()),this,SLOT(hadreadyread()));
}
user::~user()
{
    delete ui;
}

void user::hadreadyread()
{
    std::string questions[5] = {"请选择密保问题","你最喜欢的颜色是什么","你最喜欢的美食是什么","你最喜欢的电影是什么","你认为中国最好的大学是哪所"};
    QByteArray recvArray = client->readAll();
    QString find1back=recvArray;
    std::string username,info;
    int secureQue;
    bool state;
    if(Decoder_findpWord1(find1back.toStdString(),username,state,secureQue,info)==0){
         qDebug("FindpWord1 data back from server error/n");
         return;
    }

    if(state==1)//用户存在
    {
        //qDebug(info);
        udata=QString::fromStdString(username);
        disconnect(client,SIGNAL(readyRead()),0,0);
        QString Que = QString::fromStdString(questions[secureQue]);
        q = new question(udata,Que,client);
        q->show();
        this->close();
    }
    else QMessageBox::information(this,"提示","用户不存在");

}

void user::on_pushButton_clicked()
{
    QString uName = ui->userName->text();
    QString phonenum = ui->phonenumber->text();
    //发送数据协议
    std::string data=Encoder_findpWord1(uName.toStdString(),phonenum.toStdString());
    QString packData = QString::fromStdString(data);
    client->write((packData.toLocal8Bit()));
}


void user::on_closeButton_clicked()
{
    close();
}

void user::on_hideButton_clicked()
{
    showMinimized();
}
//！！！！以下东西不用动！！！！
void user::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void user::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton&&p.x()!=0&&p.y()!=0)
    {
        //移到左上角
        move(e->globalPos() - p);
    }

}

void user::mouseReleaseEvent(QMouseEvent *event){
    p.setX(0);
    p.setY(0);
}
