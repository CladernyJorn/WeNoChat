#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QWidget>
#include <string>
#include <QTreeWidget>
#include <QImage>

namespace Ui {
class FriendList;
struct User : public QObjectUserData
{
    std::string userName;
    QImage image;
};

class FriendList : public QWidget
{
    Q_OBJECT

public:
    QTreeWidget* friendlist;
    enum ItemType{isGroup = Qt::UserRole, UserInfo = Qt::UserRole + 1};
    explicit FriendList(QTreeWidget *widget, std::vector<std::string> userInfoList, QWidget *parent = 0);
    ~FriendList();

private:
    void initFriendList(std::vector<std::string> userInfoList);
    void initConnection();

signals:
    void openChatroom(QVariant variant);

private slots:
    void showFriendListMenu(QPoint pos);


//private slots:
//    void groupExpand(QTreeWidgetItem* item);
};
}

Q_DECLARE_METATYPE(Ui::User)

#endif // FRIENDLIST_H
