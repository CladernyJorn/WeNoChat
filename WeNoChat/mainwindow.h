#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QString ud,QTcpSocket * sock,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_closeButton_clicked();

    void on_hideButton_clicked();

    void on_send_clicked();

    void hadreadyread();

private:
    Ui::MainWindow *ui;
    QTcpSocket *client;
    QString udata;
};

#endif // MAINWINDOW_H
