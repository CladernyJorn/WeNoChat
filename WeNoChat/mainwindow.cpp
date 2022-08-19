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

//测试用函数，正式发布务必删除（相关控件
void MainWindow::on_pushButton_2_clicked()
{
    if(ui->listWidget->count()==0)return;
    delete ui->listWidget->item(ui->listWidget->count()-1);
}
//测试用函数，正式发布务必删除（相关控件
void MainWindow::on_pushButton_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    pushMessageIntoChatWindow(false,msg,QString::number(QDateTime::currentDateTime().toTime_t()),false);
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

    //测试发数据
    pushMessageIntoChatWindow(true,msg,QString::number(QDateTime::currentDateTime().toTime_t()),false);

    client->write(packData.toLocal8Bit());
    ui->textEdit->clear();
}

/*
 * pushMessageIntoChatWindow函数说明
 * bool type：发给别人消息，右侧气泡==true；接收到消息，左侧气泡==false。
 * QString msg：发送/接收的文本。
 * QString time：消息时间。
 *      参考：time = QString::number(QDateTime::currentDateTime().toTime_t());
 * bool isSending = false：是否正在发送，大概率用不到所以先设置成false
 *      仅发送消息有效，接收消息时这里可以随便赋值。
 *
 * *******注意********
 * ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓特别注意↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
 * ①   UI修改时需要全局搜索替换widthWithoutListWidget的值
 *      该值是整个mainWindow去掉ListWidget对话框的宽度
 *      不替换可能对话框显示大小异常
 * ②   TODO：检查可能有内存溢出，注意delete ui->listWidget->item(i);
 *      for循环将所有都删掉
 * ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
 * 注意处理空消息，空消息最好别传进来，传进来也不会显示
 * 如果是发消息，注意清空输入框
 * TODO：不清楚分辨率和缩放的影响，可能会有小概率长文本显示横向拖动条
*/
void MainWindow::pushMessageIntoChatWindow(bool type,QString msg,QString time,bool isSending = false)
{
    if(msg == ""){
        //TODO：是不是要报个错？
        return;
    }
    qDebug()<<"addMessage" << msg << time << ui->listWidget->count();
    if(type) {
        if(isSending) {
            dealMessageTime(time);
            ChatMessageWidget* messageW = new ChatMessageWidget(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, ChatMessageWidget::User_Me);
        } else {
            bool isOver = true;
            for(int i = ui->listWidget->count() - 1; i > 0; i--) {
                ChatMessageWidget* messageW = (ChatMessageWidget*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if(messageW->text() == msg) {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if(isOver) {
                dealMessageTime(time);
                ChatMessageWidget* messageW = new ChatMessageWidget(ui->listWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                dealMessage(messageW, item, msg, time, ChatMessageWidget::User_Me);
                messageW->setTextSuccess();
            }
        }
    } else {
        dealMessageTime(time);
        ChatMessageWidget* messageW = new ChatMessageWidget(ui->listWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, msg, time, ChatMessageWidget::User_She);
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void MainWindow::dealMessage(ChatMessageWidget *messageW, QListWidgetItem *item, QString text, QString time,  ChatMessageWidget::User_Type type)
{
    messageW->setFixedWidth(ui->listWidget->width() - 25);
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void MainWindow::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        ChatMessageWidget* messageW = (ChatMessageWidget*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        ChatMessageWidget* messageTime = new ChatMessageWidget(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(ui->listWidget->width() - 25, 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, ChatMessageWidget::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

