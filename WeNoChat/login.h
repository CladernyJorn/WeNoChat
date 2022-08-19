#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "mainwindow.h"
#include "forgotpwd.h"
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
private slots:
    void on_closeButton_clicked();

    void on_pushButton_2_clicked();

    void on_loginButton_clicked();

    void on_registButton_clicked();

    void on_registButton_2_clicked();

private:
    Ui::login *ui;
    QPoint p;
    void showMainWindow();
    void showRegistWindow();
    void showForgotPwdWindow();
    MainWindow * mw;
    Regist * rw;
    ForgotPwd * fw;
};

#endif // LOGIN_H
