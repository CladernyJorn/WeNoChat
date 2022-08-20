#include "password.h"
#include "ui_password.h"

password::password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::password)
{
    ui->setupUi(this);
}

password::password(QString u,QTcpSocket *sock,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::password)
{
    ui->setupUi(this);
    client = sock;
    uname = u;
    connect(client,SIGNAL(readyRead()),this,SLOT(hadreadyread()));
}

password::~password()
{
    delete ui;
}

void password::hadreadyread()
{
    QByteArray recvArray = client->readAll();
    QString find3back=recvArray;
    std::string username;
    bool state;
    if(Decoder_findpWord3(find3back.toStdString(),username,state)==0){
        qDebug("Regist data back from server error/n");
        return;
    }
    if(state==1)//注册成功
    {
        //qDebug(info);
        disconnect(client,SIGNAL(readyRead()),0,0);
        mw = new MainWindow(uname,client);
        mw->show();
        this->close();
    }
    else QMessageBox::information(this,"提示","密码更新失败");

}

void password::on_confirm_clicked()
{
    QString pwd = ui->passw->text();
    QString pwd_2 = ui->passw_2->text();
    qDebug()<<pwd<<pwd_2;
    //两次密码相同
    if(pwd == pwd_2)
    {
        //与服务器连接，检查注册
        std::string data=Encoder_findpWord3(uname.toStdString(),pwd.toStdString());
        QString packData = QString::fromStdString(data);
        client->write((packData.toLocal8Bit()));
    }
    else
    {
        QMessageBox::information(this,"提示","密码不一致");
    }
}
