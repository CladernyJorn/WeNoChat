#include "login.h"
#include "ui_login.h"
#include <QMouseEvent>
#include<QPainter>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
    //连接服务器
    client = new QTcpSocket();
    client->connectToHost("172.16.240.133",8899);
    connect(client,SIGNAL(connected()),this,SLOT(hadconnected()));
}

//成功连接服务器
void login::hadconnected()
{
    ui->loginButton->setEnabled(true);
    connect(client,SIGNAL(readyRead()),this,SLOT(hadreadyread()));
}

//准备读取服务器内容
void login::hadreadyread()
{
    QByteArray recvArray = client->readAll();
    if(recvArray.at(0) != '#' || recvArray.at(recvArray.size()-1) != '&')
        return ;
    QString recvStr = QString::fromLocal8Bit(recvArray);
    recvStr = recvStr.mid(1,recvStr.length()-2);
    //qDebug()<<recvStr;

    QStringList recvList = recvStr.split('|');
    //获取登录信息
    if(recvList.size() < 3)
        return;
    //qDebug()<<recvList;
    if(recvList[0] == "1")
    {
        if(recvList[1] == "1")
        {
            QMessageBox::information(this,"提示",recvList[2]);
        }
        else
        {
            disconnect(client,SIGNAL(readyRead()),0,0);
            showMainWindow();
            this->close();
        }
    }
    if(recvList[0] == "2")
    {
        if(recvList[1] == "0")
        {
            QMessageBox::information(this,"提示",recvList[2]);
            rw->close();
            rw = NULL;
        }
        else
        {
            QMessageBox::information(this,"提示",recvList[2]);
        }
    }
    if(recvList[0] == "3")
    {

    }
}

void login::on_loginButton_clicked()
{
    //获取输入框内容
    QString userName = ui->userEdit->text();
    QString userPassword = ui->passwordEdit->text();
    //向服务器发送登录数据
    //TODO:发送数据协议
    QString packData = userName + userPassword;
    client->write((packData.toLocal8Bit()));
}

//新窗体相关函数
//打开聊天主界面
void login::showMainWindow(){
    mw = new MainWindow(udata,client);
    mw->show();
}
//打开注册界面
void login::showRegistWindow(){
    //TODO：这里检查一下禁止多开会更好，但是好像不能通过判断NULL来检查
    rw = new Regist(client);
    rw->show();
}
//打开忘记密码界面
void login::showForgotPwdWindow(){
    //TODO：这里检查一下禁止多开会更好，但是好像不能通过判断NULL来检查
    fw = new ForgotPwd();
    fw->show();
}

//！！！！以下东西不用动！！！！
void login::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void login::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }

}

login::~login()
{
    delete ui;
}

void login::on_closeButton_clicked()
{
    this->close();
}

void login::on_hideButton_clicked()
{
    showMinimized();
}



void login::on_registButton_clicked()
{
    showRegistWindow();
}

void login::on_forgetButton_clicked()
{
    showForgotPwdWindow();
}
