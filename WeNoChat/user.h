#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include "question.h"

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    explicit user(QTcpSocket *sock,QWidget *parent = 0);
    ~user();

private slots:

    void hadreadyread();

    void on_pushButton_clicked();

private:
    Ui::user *ui;
    QTcpSocket *client;
    question *q;
    QString udata;
};

#endif // USER_H
