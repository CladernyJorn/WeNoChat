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
    if(1)
    {
        disconnect(client,SIGNAL(readyRead()),0,0);
        mw = new MainWindow(uname,client);
        mw->show();
        this->close();
    }
    else
    {
        qDebug()<<"mimacuowu";
    }
}

void password::on_confirm_clicked()
{
    QString pwd = ui->passw->text();
    QString pwd_2 = ui->passw_2->text();
    qDebug()<<pwd<<pwd_2;
    //两次密码相同
    if(pwd == pwd_2)
    {
        client->write(pwd.toLocal8Bit());
    }
    else
    {
        QMessageBox::information(this,"提示","密码不一致");
    }
}
