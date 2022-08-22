#ifndef REGIST_H
#define REGIST_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include"communicate_utils.h"
#include "mainwindow.h"
namespace Ui {
class Regist;
}

class Regist : public QWidget
{
    Q_OBJECT

public:
    explicit Regist(QWidget *parent = 0);
    explicit Regist(QTcpSocket *sock,QWidget *parent = 0);
    ~Regist();

protected:
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void hadreadyread();
    void on_loginButton_clicked();

    void on_closeButton_clicked();

    void on_hideButton_clicked();

private:
    void showMainWindow();
    Ui::Regist *ui;
    QTcpSocket *client;
    MainWindow * mw;
    QString udata;
    QPoint p;
};

#endif // REGIST_H
