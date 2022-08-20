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

private slots:
    void hadreadyread();

    void on_confirm_clicked();

private:
    Ui::password *ui;
    QTcpSocket *client;
    MainWindow *mw;
    QString uname;
};

#endif // PASSWORD_H