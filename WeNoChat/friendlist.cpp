#include "friendlist.h"
#include "ui_mainwindow.h"
#include"mydelegate.h"
#include <QLabel>
#include <QIcon>
#include <QDebug>
#include <QTreeWidget>
#include <QMenu>

Ui::FriendList::FriendList(QTreeWidget *widget, std::vector<Ui::User> userList, QWidget *parent) : QWidget(parent), friendlist(widget)
{
    qDebug("in");
    //    zszs
    //    std::vector<std::string> userList;
    //    userList.push_back("user_2");
    //    userList.push_back("user_3");
    //    userList.push_back("user_1");

    initFriendList(userList);
    initConnection();
    qDebug("out");
}

Ui::FriendList::~FriendList() {}

void Ui::FriendList::initFriendList(std::vector<Ui::User> userInfoList)
{

    friendlist->setHeaderHidden(true);
    friendlist->setIndentation(0);
    friendlist->setAnimated(true);

    QTreeWidgetItem *group_default = new QTreeWidgetItem();
    group_default->setText(0, "我的好友");
    group_default->setData(0, isGroup, 1);
    groups["default"] = group_default;
    friendlist->addTopLevelItem(group_default);
    friendlist->sortByColumn(0);
    friendlist->setItemDelegate(new MyDelegate);
    addFriendInfo(group_default, userInfoList);
}

void Ui::FriendList::initConnection()
{
    connect(friendlist, &QTreeWidget::itemClicked, [&](QTreeWidgetItem *item)
            {
        if (item->data(0, isGroup).toBool())
        {
            item->setExpanded(!item->isExpanded());
        } });
    connect(friendlist, &QTreeWidget::itemDoubleClicked, [&](QTreeWidgetItem *item)
            {
        if (!item->data(0, isGroup).toBool())
        {
            emit openChatroom(QVariant::fromValue(item->data(0, UserInfo).value<Ui::User>()));
        } });

    friendlist->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(friendlist, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showFriendListMenu(QPoint)));
}

void Ui::FriendList::showFriendListMenu(QPoint pos)
{
    QMenu *menu = new QMenu;
    QTreeWidgetItem *item = friendlist->itemAt(pos);
    if (item)
    {
        qDebug() << QString(item->data(0, isGroup + 1).value<Ui::User>().userName.c_str());
        qDebug() << item->data(0, isGroup).toBool();
        if (!item->data(0, isGroup).toBool())
        {
            QAction *action1 = new QAction("打开对话");
            //            QAction* action2 = new QAction("置顶");
            QAction *action3 = new QAction("消息记录");
            QAction *action4 = new QAction("移动好友至");
            menu->addAction(action1);
            //            menu->addAction(action2);
            menu->addAction(action3);
            menu->addAction(action4);
            connect(action1, &QAction::triggered, [&, item]()
                    { emit openChatroom(QVariant::fromValue(item->data(0, UserInfo).value<Ui::User>())); });
            menu->move(friendlist->cursor().pos());
            menu->show();
        }
        else
        {
            QAction *action1 = new QAction("添加分组");
            QAction *action2 = new QAction("重命名");
            QAction *action3 = new QAction("删除");
            menu->addAction(action1);
            menu->addAction(action2);
            menu->addAction(action3);
            menu->move(friendlist->cursor().pos());
            menu->show();
        }
    }
    else
    {
        qDebug() << "here";
    }
}

void Ui::FriendList::addFriendInfo(QTreeWidgetItem *group, std::vector<Ui::User> friendInfoList)
{
    QList<QTreeWidgetItem*> list;

    for (Ui::User f:friendInfoList)
    {
        QTreeWidgetItem* friendRecord = new QTreeWidgetItem();

        friendRecord->setText(0, QString(f.userName.c_str()));
        friendRecord->setData(0, isGroup, 0);


        QImage *img = new QImage;
        img->load(":/assets/defaultHead.png");
        if(f.image.isNull())
        {
            friendRecord->setIcon(0,QIcon(QPixmap::fromImage(*img)));
        }
        else
        {
            friendRecord->setIcon(0,QIcon(QPixmap::fromImage(f.image)));
        }
        friendRecord->setFont(0, QFont("consolas", 15, QFont::Normal));

        friendRecord->setData(0, UserInfo, QVariant::fromValue(f));
        list.append(friendRecord);
    }

    group->addChildren(list);
    group->sortChildren(0, Qt::AscendingOrder);
}

void Ui::FriendList::addGroup(std::string name)
{
    groups[name] = new QTreeWidgetItem();
}
void Ui::FriendList::insertToGroup(std::string groupName, std::vector<Ui::User> friendInfoList)
{
    auto pgroup = groups.find(groupName);
    if(pgroup!=groups.end())
    {
        addFriendInfo(pgroup->second, friendInfoList);
    }
}
void Ui::FriendList::deleteGroup(std::string name)
{

}
