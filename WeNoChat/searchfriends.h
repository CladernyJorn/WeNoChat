#ifndef SEARCHFRIENDS_H
#define SEARCHFRIENDS_H

#include <QDialog>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include"communicate_utils.h"
namespace Ui {
class searchFriends;
}

class searchFriends : public QDialog
{
    Q_OBJECT

public:
    explicit searchFriends(QWidget *parent = 0);
    explicit searchFriends(QString u,QTcpSocket * sock,QWidget *parent = 0);
    ~searchFriends();

private slots:
    void on_pushButton_clicked();

private:
    Ui::searchFriends *ui;
    QTcpSocket *client;
    QString udata;
};

#endif // SEARCHFRIENDS_H
