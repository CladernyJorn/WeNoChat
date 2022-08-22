#include "regist.h"
#include "ui_regist.h"
#include <QMouseEvent>
#include<QPainter>

Regist::Regist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Regist)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
    ui->comboBox->addItem("请选择密保问题");
    ui->comboBox->addItem("你最喜欢的颜色是什么");
    ui->comboBox->addItem("你最喜欢的美食是什么");
    ui->comboBox->addItem("你最喜欢的电影是什么");
    ui->comboBox->addItem("你认为中国最好的大学是哪所");
}

Regist::Regist(QTcpSocket *sock,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Regist)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
    client = sock;
    ui->comboBox->addItem("请选择密保问题");
    ui->comboBox->addItem("你最喜欢的颜色是什么");
    ui->comboBox->addItem("你最喜欢的美食是什么");
    ui->comboBox->addItem("你最喜欢的电影是什么");
    ui->comboBox->addItem("你认为中国最好的大学是哪所");
    connect(client,SIGNAL(readyRead()),this,SLOT(hadreadyread()));

}

//注册按钮按下：在这里处理注册
void Regist::on_loginButton_clicked()
{
    QString temp = ui->comboBox->currentText();
    if(temp == "请选择密保问题")
    {
        QMessageBox::information(this,"提示","请选择密保问题");
        return;
    }
    QString userName = ui->userEdit->text();
    QString pwd = ui->passwordEdit->text();
    //TODO：判断密码合法性，不能包含特殊符号
    QString pwd2 = ui->passwordEdit_2->text();
    //判断两次相同
    if(pwd != pwd2){
        QMessageBox::information(this,"提示","密码不一致");
        return;
    }
    QString phoneNumber = ui->phoneNumberEdit->text();
    int question = ui->comboBox->currentIndex();
    QString answer = ui->answerEdit->text();
    //与服务器连接，检查注册
    std::string data=Encoder_regist(userName.toStdString(),pwd.toStdString(),phoneNumber.toStdString(),question,answer.toStdString());
    QString packData = QString::fromStdString(data);
    client->write((packData.toLocal8Bit()));
}
//准备读取服务器内容
void Regist::hadreadyread()
{
    QByteArray recvArray = client->readAll();
    QString registback=recvArray;
    std::string username,info;
    bool state;
    if(Decoder_regist(registback.toStdString(),username,info,state)==0){
        qDebug("Regist data back from server error/n");
        return;
    }
    if(state==1)//注册成功
    {
        //qDebug(info);
        udata=QString::fromStdString(username);
        disconnect(client,SIGNAL(readyRead()),0,0);
        showMainWindow();
        this->close();
    }
    else QMessageBox::information(this,"提示","注册成功");

}
//打开聊天主界面
void Regist::showMainWindow(){
    mw = new MainWindow(udata,client);
    mw->show();
}
//！！！！以下东西不用动！！！！
void Regist::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void Regist::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton&&p.x()!=0&&p.y()!=0)
    {
        //移到左上角
        move(e->globalPos() - p);
    }

}
void Regist::mouseReleaseEvent(QMouseEvent *event){
    p.setX(0);
    p.setY(0);
}

void Regist::on_closeButton_clicked()
{
    close();
}

void Regist::on_hideButton_clicked()
{
    showMinimized();
}

Regist::~Regist()
{
    delete ui;
}
