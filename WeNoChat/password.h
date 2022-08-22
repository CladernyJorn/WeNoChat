#ifndef PASSWORD_H
#define PASSWORD_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"

namespace Ui {
class password;
}

class password : public QWidget
{
    Q_OBJECT

public:
    explicit password(QWidget *parent = 0);
    explicit password(QString u,QTcpSocket *sock,QWidget *parent = 0);
    ~password();
protected:
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void hadreadyread();

    void on_confirm_clicked();

    void on_closeButton_clicked();

    void on_hideButton_clicked();

private:
    Ui::password *ui;
    QTcpSocket *client;
    MainWindow *mw;
    QString uname;
    QPoint p;
};

#endif // PASSWORD_H
