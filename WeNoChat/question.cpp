#include "question.h"
#include "ui_question.h"

question::question(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::question)
{
    ui->setupUi(this);
}

question::question(QString q,QTcpSocket *sock,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::question)
{
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
    qDebug()<<recvArray;
    //确认用户密保问题
    if(1)
    {
        disconnect(client,SIGNAL(readyRead()),0,0);
        pass = new password(qu,client);
        pass->show();
        this->close();
    }
    else
    {
        QMessageBox::information(this,"提示","密保问题错误");
    }
}


void question::on_confirmButton_clicked()
{
    qDebug()<<"question";
    QString an = ui->answer->text();
    client->write(an.toLocal8Bit());
}
