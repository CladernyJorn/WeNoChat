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
protected:
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_closeButton_clicked();

    void on_hideButton_clicked();

private:
    Ui::searchFriends *ui;
    QTcpSocket *client;
    QString udata;
    QPoint p;
};

#endif // SEARCHFRIENDS_H
