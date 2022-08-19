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

}

void login::on_loginButton_clicked()
{
    //获取输入框内容
    QString userName = ui->userEdit->text();
    QString userPassword = ui->passwordEdit->text();
    //TODO：校验，与服务器连接

    //调用进入下一个界面的函数，函数在下方实现，注意.h文件同步修改参数
    showMainWindow();
    close();
}

//新窗体相关函数
//打开聊天主界面
void login::showMainWindow(){
    mw = new MainWindow();
    mw->show();
}
//打开注册界面
void login::showRegistWindow(){
    //TODO：这里检查一下禁止多开会更好，但是好像不能通过判断NULL来检查
    rw = new Regist();
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
    close();
}

void login::on_pushButton_2_clicked()
{
    showMinimized();
}



void login::on_registButton_clicked()
{
    showRegistWindow();
}

void login::on_registButton_2_clicked()
{
    showForgotPwdWindow();
}
