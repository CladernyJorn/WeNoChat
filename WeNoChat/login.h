#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "user.h"
#include "regist.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

protected:
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

public slots:
    void hadconnected();

private slots:
    void hadreadyread();

    void on_closeButton_clicked();

    void on_hideButton_clicked();

    void on_loginButton_clicked();

    void on_registButton_clicked();

    void on_forgetButton_clicked();

private:
    Ui::login *ui;
    QPoint p;
    QTcpSocket *client;
    QString udata;
    void showMainWindow();
    void showRegistWindow();
    void showForgotPwdWindow();
    MainWindow * mw;
    Regist * rw;
    user *u;
};

#endif // LOGIN_H
