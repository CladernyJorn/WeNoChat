#include "group.h"
#include "ui_group.h"

group::group(Ui::FriendList *f,QWidget *parent) :
    QWidget(parent),
    client(DataSock::get()),
    ui(new Ui::group)
{
    ui->setupUi(this);
    friendlist = f;
    for(int i = 0; i < ; i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        QCheckBox *checkbox = new QCheckBox();

        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,checkbox);
        //TODO:设置好友列表
        checkbox->setText(friendlist->groups["default"]->child(i)->text(0));

        connect(checkbox, SIGNAL(stateChanged(int)),this,SLOT(anystateChanged()));
    }
}

group::~group()
{
    delete ui;
}

void group::anystateChanged()
{
    selectedItems.clear();
    for(int i = 0;i < ; i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QCheckBox *checkbox = static_cast<QCheckBox *>(ui->listWidget->itemWidget(item));
        if(checkbox->isChecked())
        {
            selectedItems.append(i);
        }
    }
}

void group::on_pushButton_clicked()
{
    QString groupname = ui->lineEdit->text();
    qDebug()<<selectedItems;
    QString user;
    for(int i = 0;i < selectedItems.size();i++)
    {
        //把群聊中好友加进去
        user += friendlist->groups["default"]->child->text(0);
    }
    std::string data = Encoder_add_group_chat(groupname.toStdString(), user.toStdString());
    QString packData = QString::fromStdString(data);
    client.sendMessage(packData);
    this->close();
}
