#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>

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
    qDebug()<<QString::number(QDateTime::currentDateTime().toTime_t());
}

void MainWindow::clearAllMessage(){
    while(ui->listWidget->count()>0){
        delete ui->listWidget->item(ui->listWidget->count()-1);
    }
}

MainWindow::MainWindow(QString ud,QTcpSocket *sock,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    udata = ud;
    client = sock;
    ui->setupUi(this);
    userList.clear();
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //TODO：没有窗口边框怎么顶部拖动？继承QLabel，重写mouseMoveEvent和press...，顶部两个label就可以实现拖动窗口了
    connect(client,SIGNAL(readyRead()),this,SLOT(hadreadyread()));

    //发送好友列表请求
    std::string data=Encoder_askfriendsList(udata.toStdString());
    QString packData = QString::fromStdString(data);
    client->write((packData.toLocal8Bit()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hadreadyread()
{

    QByteArray recvArray = client->readAll();
    //区分是chat信息还是好友列表信息
    QString backdata=recvArray;
    Json::Reader reader;
    Json::Value jtmp,tmp_info;
    if (!reader.parse(backdata.toStdString(), jtmp)){
        qDebug()<<"服务器返回信息错误\n";
        return ;
    }
    if(jtmp["type"].asString()=="askfriendsList"){//处理好友列表信息
        std::string username,info;
        bool state;
        if(Decoder_askfriendsList(backdata.toStdString(),username,userList)==0){
             qDebug("askfriends data back from server error/n");
             return;
        }

        /*Todo:使用userList生成好友列表*/
        friendList = new Ui::FriendList(ui->friendList, userList);
        initConnection();
    }
    else if(jtmp["type"].asString()=="chat"){//处理聊天信息
        std::string sender_username,msg;
        if(Decoder_chat(backdata.toStdString(),sender_username,msg)==0){
             qDebug("chat data back from server error/n");
             return;
        }
        pushMessageIntoChatWindow(false,QString::fromStdString(msg),QString::number(QDateTime::currentDateTime().toTime_t()),false);
    }
    else if(jtmp["type"].asString()=="addfriends"){//mainwindow里处理加好友的返回信息
        std::string friend_username;
        bool state;
        if(Decoder_addfriends(backdata.toStdString(),friend_username,state)==0){
             qDebug("addfriends data back from server error/n");
             return;
        }
        if(state==1){
            /*Todo:在列表里添加这个新的好友
             *
             *
             */
            QMessageBox::information(this,"提示",("成功添加好友"+friend_username).c_str());//
        }
        else QMessageBox::information(this,"提示","该好友不存在");
    }
    else{
        qDebug()<<"服务器返回信息错误\n";
        return ;
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
    QString msg=ui->textEdit->toPlainText();
    if(msg.isEmpty())return;//空字符不发送
    /*Todo :根据好友列表生成要发送信息好友usersList
     * 这里暂时用hxy代替
     *
     */
    std::vector<std::string>usersList={"hxy"};
    //发送数据协议
    std::string data=Encoder_chat(udata.toStdString(),msg.toStdString(),usersList);
    QString packData = QString::fromStdString(data);
    client->write((packData.toLocal8Bit()));
    //测试发数据
    pushMessageIntoChatWindow(true,msg,QString::number(QDateTime::currentDateTime().toTime_t()),false);
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
 * QImage* image = NULL:头像指针，默认为NULL，则显示默认头像。
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
void MainWindow::pushMessageIntoChatWindow(bool type,QString msg,QString time,QImage* image,bool isSending)
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
            dealMessage(messageW, item, msg, time, ChatMessageWidget::User_Me, image);
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
                dealMessage(messageW, item, msg, time, ChatMessageWidget::User_Me,image);
                messageW->setTextSuccess();
            }
        }
    } else {
        dealMessageTime(time);
        ChatMessageWidget* messageW = new ChatMessageWidget(ui->listWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, msg, time, ChatMessageWidget::User_She,image);
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void MainWindow::dealMessage(ChatMessageWidget *messageW, QListWidgetItem *item, QString text, QString time,  ChatMessageWidget::User_Type type,QImage* image)
{
    messageW->setFixedWidth(ui->listWidget->width() - 25);
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type, image);
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


void MainWindow::on_pushButton_addfriend_clicked()
{
    add = new searchFriends(udata,client);
    add->show();
}

void MainWindow::initConnection()
{
    connect(friendList, SIGNAL(openChatroom(QVariant)), this, SLOT(startChatting(QVariant)));
}

void MainWindow::startChatting(QVariant variant)
{
    clearAllMessage();

    Ui::User chatFriend = variant.value<Ui::User>();
    qDebug()<<"here";
    qDebug() << QString(chatFriend.userName.c_str());
    ui->chatName->setText("   " + QString(chatFriend.userName.c_str()));
    chattingInfo.chatFriend = chatFriend;

    std::vector<std::string> messages;
    messages.push_back("user1/你好/1661088000");
    messages.push_back("111/你好/1661088100");
    messages.push_back("user1/很高兴认识你/1661088200");
    messages.push_back("111/我也是/1661088290");
    chattingInfo.record = new MessageRecord(messages);
    for(std::string rec : chattingInfo.record->getAllMessageRecord())
    {
        QStringList list = QString(rec.c_str()).split("/");
        if(list[0] == udata){
            //传自己头像的 Qimage
            pushMessageIntoChatWindow(true, list[1], list[2]);
        }else{
            //传对方头像的QImage
            pushMessageIntoChatWindow(false, list[1], list[2]);
        }

    }
}



//以下是拖动窗口的代码
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = ev->globalPos() - this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::LeftButton&&p.x()!=0&&p.y()!=0)
    {
        //移到左上角
        move(ev->globalPos() - p);
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev){
    p.setX(0);
    p.setY(0);
}
