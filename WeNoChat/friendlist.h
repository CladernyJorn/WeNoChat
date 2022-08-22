#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QWidget>
#include <string>
#include <QTreeWidget>
#include <QImage>
#include<map>
#include<string>
namespace Ui
{
    class FriendList;
    struct User : public QObjectUserData
    {
        std::string userName;
        QImage image;
//        std::string imageStr;
    };

    class FriendList : public QWidget
    {
        Q_OBJECT

    public:
        QTreeWidget *friendlist;
        enum ItemType
        {
            isGroup = Qt::UserRole,
            UserInfo = Qt::UserRole + 1
        };
        explicit FriendList(QTreeWidget *widget, std::vector<Ui::User> userInfoList, QWidget *parent = 0);
        ~FriendList();
        void addFriendInfo(QTreeWidgetItem *group, std::vector<Ui::User> friendInfoList);
        void addGroup(std::string name);
        void insertToGroup(std::string, std::vector<Ui::User> friendInfoList);
        void deleteGroup(std::string name);
        //TODO: delete friend;

    private:
        void initFriendList(std::vector<Ui::User> userInfoList);
        void initConnection();

        std::map<std::string, QTreeWidgetItem *> groups;

    signals:
        void openChatroom(QVariant variant);

    private slots:
        void showFriendListMenu(QPoint pos);

        // private slots:
        //     void groupExpand(QTreeWidgetItem* item);
    };
}

Q_DECLARE_METATYPE(Ui::User)

#endif // FRIENDLIST_H
