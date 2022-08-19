#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //TODO：没有窗口边框怎么顶部拖动？继承QLabel，重写mouseMoveEvent和press...，顶部两个label就可以实现拖动窗口了
}

MainWindow::MainWindow(QString ud,QTcpSocket *sock,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    udata = ud;
    client = sock;
    ui->setupUi(this);
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //TODO：没有窗口边框怎么顶部拖动？继承QLabel，重写mouseMoveEvent和press...，顶部两个label就可以实现拖动窗口了
    connect(client,SIGNAL(readyRead()),this,SLOT(hadreadyread()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hadreadyread()
{
    QByteArray recvArray = client->readAll();
    //QDebug()<<recvArray;

    if(recvArray.at(0) != '#' || recvArray.at(recvArray.size()-1) != '&')
        return ;
    QString recvStr = QString::fromLocal8Bit(recvArray);
    recvStr = recvStr.mid(1,recvStr.length()-2);
    //qDebug()<<recvStr;

    QStringList recvList = recvStr.split('|');
    //获取登录信息
    if(recvList.size() < 3)
        return;
    if(recvList[0] == "3")
    {
        //呈现聊天记录
    }
}

void MainWindow::on_hideButton_clicked()
{
    showMinimized();
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

void MainWindow::on_send_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    QString packData = udata + msg;

    client->write(packData.toLocal8Bit());
    ui->textEdit->clear();
}
