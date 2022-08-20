#include "question.h"
#include "ui_question.h"

question::question(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::question)
{
    ui->setupUi(this);
}

question::question(QString user,QString q,QTcpSocket *sock,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::question)
{
    udata=user;
    ui->setupUi(this);
    client = sock;
    qu = q;
    ui->question_2->setText(qu);
    connect(client,SIGNAL(readyRead()),this,SLOT(hadreadyread()));
}

question::~question()
{
    delete ui;
}

void question::hadreadyread()
{
    QByteArray recvArray = client->readAll();
    QString find2back=recvArray;
    std::string username;
    bool state;
    if(Decoder_findpWord2(find2back.toStdString(),username,state)==0){
        qDebug("FindpWord2 data back from server error/n");
        return;
    }
    if(state==1)//注册成功
    {
        //qDebug(info);
        disconnect(client,SIGNAL(readyRead()),0,0);
        pass = new password(udata,client);
        pass->show();
        this->close();
    }
    else QMessageBox::information(this,"提示","密保问题错误");
}


void question::on_confirmButton_clicked()
{
    QString ans=ui->answer->text();
    //发送数据协议
    std::string data=Encoder_findpWord2(udata.toStdString(),ans.toStdString());
    QString packData = QString::fromStdString(data);
    client->write((packData.toLocal8Bit()));
}
