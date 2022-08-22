#include "login.h"
#include "ui_login.h"
#include <QMouseEvent>
#include <QPainter>

login::login(QWidget *parent) : QWidget(parent),
                                ui(new Ui::login)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
    //连接服务器
    client = new QTcpSocket();
    client->connectToHost("192.168.1.112", 8888);
    connect(client, SIGNAL(connected()), this, SLOT(hadconnected()));
}

//成功连接服务器
void login::hadconnected()
{
    ui->loginButton->setEnabled(true);
    ui->loginButton->setText("登录");
    ui->forgetButton->setEnabled(true);
    ui->registButton->setEnabled(true);
    connect(client, SIGNAL(readyRead()), this, SLOT(hadreadyread()));
}

//准备读取服务器内容
void login::hadreadyread()
{
    QByteArray recvArray = client->readAll();
    QString loginback = recvArray;

    Json::Reader reader;
    Json::Value jtmp;

    if (!reader.parse(loginback.toStdString(), jtmp))
    {
        qDebug() << "服务器返回信息错误\n";
        return;
    }
    if (!jtmp.isObject())
    {
        qDebug() << "服务器返回信息错误\n";
        return;
    }
    std::string username, info;
    bool state;
    if (Decoder_login(jtmp["info"], username, info, state) == 0)
    {
        qDebug("Login data back from server error/n");
        return;
    }

    if (state == 1) //登陆成功
    {
        // qDebug(info);
        udata = QString::fromStdString(username);
        disconnect(client, SIGNAL(readyRead()), 0, 0);
        showMainWindow();
        this->close();
    }
    else
        QMessageBox::information(this, "提示", info.c_str());
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
    client->write((packData.toLocal8Bit()));
    //    showMainWindow();
}

//新窗体相关函数
//打开聊天主界面
void login::showMainWindow()
{
    mw = new MainWindow(udata, client);
    mw->show();
}
//打开注册界面
void login::showRegistWindow()
{
    // TODO：这里检查一下禁止多开会更好，但是好像不能通过判断NULL来检查
    rw = new Regist(client);
    rw->show();
}
//打开忘记密码界面
void login::showForgotPwdWindow()
{
    // TODO：这里检查一下禁止多开会更好，但是好像不能通过判断NULL来检查
    u = new user(client);
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
    disconnect(client, SIGNAL(readyRead()), 0, 0);
    showRegistWindow();

    this->close();
}

void login::on_forgetButton_clicked()
{
    disconnect(client, SIGNAL(readyRead()), 0, 0);
    showForgotPwdWindow();
    this->close();
}
