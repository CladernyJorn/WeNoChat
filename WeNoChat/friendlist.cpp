#include "friendlist.h"
#include "ui_mainwindow.h"

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
    friendlist->addTopLevelItem(group_default);
    friendlist->sortByColumn(0);

    // zszs
    //     QTreeWidgetItem* FixedFrame = new QTreeWidgetItem();
    //     FixedFrame->setText(0, "11111");
    //     group_1->addChild(FixedFrame);
    //     FixedFrame->setData(0, isGroup, 0);

    QList<QTreeWidgetItem *> list;

    for (unsigned int i = 0; i < userInfoList.size(); ++i)
    {
        QTreeWidgetItem *friendRecord = new QTreeWidgetItem();
        friendRecord->setText(0, QString::fromStdString(userInfoList[i].userName));
        friendRecord->setData(0, isGroup, 0);
        list.append(friendRecord);
        Ui::User f;
        f = userInfoList[i];
        friendRecord->setData(0, UserInfo, QVariant::fromValue(f));
    }

    group_default->addChildren(list);
    group_default->sortChildren(0, Qt::AscendingOrder);
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
