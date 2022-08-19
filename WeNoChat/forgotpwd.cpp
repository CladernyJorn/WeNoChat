#include "forgotpwd.h"
#include "ui_forgotpwd.h"
#include <QMouseEvent>
#include<QPainter>
ForgotPwd::ForgotPwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPwd)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
}

void ForgotPwd::on_loginButton_clicked()
{
    QString userName = ui->userEdit->text();
    QString pwd = ui->passwordEdit->text();
    //TODO：判断密码合法性，不能包含特殊符号
    QString pwd2 = ui->passwordEdit_2->text();
    //判断两次相同
    if(pwd != pwd2){
        //TODO：messageBox警告
        return;
    }
    QString phoneNumber = ui->phoneNumberEdit->text();
    QString question = ui->questionEdit->text();
    QString answer = ui->answerEdit->text();
    //TODO：与服务器连接，找回密码
}


//！！！！以下东西不用动！！！！
void ForgotPwd::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void ForgotPwd::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }

}
void ForgotPwd::on_closeButton_clicked()
{
    close();
}

void ForgotPwd::on_hideButton_clicked()
{
    showMinimized();
}

ForgotPwd::~ForgotPwd()
{
    delete ui;
}


