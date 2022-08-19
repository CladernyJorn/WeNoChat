#ifndef FORGOTPWD_H
#define FORGOTPWD_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class ForgotPwd;
}

class ForgotPwd : public QWidget
{
    Q_OBJECT

public:
    explicit ForgotPwd(QWidget *parent = 0);
    ~ForgotPwd();

protected:
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

private slots:
    void on_closeButton_clicked();

    void on_hideButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::ForgotPwd *ui;
    QPoint p;
};

#endif // FORGOTPWD_H
