#ifndef REGIST_H
#define REGIST_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>

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

private slots:
    void on_loginButton_clicked();

    void on_closeButton_clicked();

    void on_hideButton_clicked();

private:
    Ui::Regist *ui;
    QTcpSocket *client;
    QPoint p;
};

#endif // REGIST_H
