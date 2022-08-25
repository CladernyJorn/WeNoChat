#include "login.h"
#include "ui_login.h"
#include <QMouseEvent>
#include "constants.h"
#include <QPainter>
#include <QFileInfo>
#include <string>
#include "utils/tools.h"
using namespace std;

login::login(QWidget *parent) : QWidget(parent),
                                ui(new Ui::login),
                                client(DataSock::get())
{
    ui->setupUi(this);

    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
    //连接服务器
    client.connectToHost(Net::addr, Net::port);

    //成功连接服务器
    client.setConnectCallback([=]()
                              {
        ui->loginButton->setEnabled(true);
        ui->loginButton->setText("登录");
        ui->forgetButton->setEnabled(true);
        ui->registButton->setEnabled(true); });

    //读取服务器内容
    client.addCallback("login", [=](const Json::Value &jtmp)
                       {
        std::string username, info;
        bool state;
        if (Decoder_login(jtmp, username, info, state) == 0)
        {
            qDebug("Login data back from server error/n");
            return;
        }

        if (state == 1) //登陆成功
        {
            // qDebug(info);
            showMainWindow(QString::fromStdString(username));
            this->close();
        }
        else
            QMessageBox::information(this, "提示", info.c_str()); });
}

void login::on_loginButton_clicked()
{
    //获取输入框内容
    QString userName = ui->userEdit->text();
    QString userPassword = ui->passwordEdit->text();
    //向服务器发送登录数据
    //发送数据协议
    std::string data = Encoder_login(userName.toStdString(), userPassword.toStdString());
    QString packData = QString::fromStdString(data);
    client.sendMessage(packData);
    //    showMainWindow();
}

//新窗体相关函数
//打开聊天主界面
void login::showMainWindow(QString udata)
{
    mw = new MainWindow(udata);
    mw->show();
}
//打开注册界面
void login::showRegistWindow()
{
    // TODO：这里检查一下禁止多开会更好，但是好像不能通过判断NULL来检查
    rw = new Regist();
    rw->show();
}
//打开忘记密码界面
void login::showForgotPwdWindow()
{
    // TODO：这里检查一下禁止多开会更好，但是好像不能通过判断NULL来检查
    u = new user();
    u->show();
}

//！！！！以下东西不用动！！！！
void login::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void login::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton && p.x() != 0 && p.y() != 0)
    {
        //移到左上角
        move(e->globalPos() - p);
    }
}

void login::mouseReleaseEvent(QMouseEvent *event)
{
    p.setX(0);
    p.setY(0);
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

    this->close();
}

void login::on_forgetButton_clicked()
{
    showForgotPwdWindow();
    this->close();
}
