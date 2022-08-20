#ifndef QUESTION_H
#define QUESTION_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include "password.h"

namespace Ui {
class question;
}

class question : public QWidget
{
    Q_OBJECT

public:
    explicit question(QWidget *parent = 0);
    explicit question(QString user,QString q,QTcpSocket *sock,QWidget *parent=0);
    ~question();

private slots:


    void hadreadyread();

    void on_confirmButton_clicked();

private:
    Ui::question *ui;
    QTcpSocket *client;
    QString qu;
    password *pass;
    QString udata;
};

#endif // QUESTION_H
