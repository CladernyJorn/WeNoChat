#ifndef WNCIMAGE_H
#define WNCIMAGE_H
#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QTcpSocket>
#include <QtNetwork>
#include <QFileDialog>
#include <QAbstractSocket>
#include"communicate_utils.h"
#include <QImage>
//定义了WNCimage类用于打包发送图片，以及单独的解压函数，用于将QString的info还原出Qimage文件
//1.QString的info -> Qimage 函数
QImage QString2Qimage(const QString& info);

//2.WNCimage发送图片
class WNCimage//图像类，封装图片，传输函数等操作
{
    /* 用于发送图片：
     * -先调用生成函数，传入图片，username和socket（具体看构造函数），
     * -之后直接调用方法就可以向服务器发送对应的json文件了
     * ---上传头像：使用void send_submit_image();
     * ---发送图片：使用void end_chatfile_image(std::vector<std::string>userList),需要传入发给谁;
     * 二者均是先向服务器发送发文件通知，然后接收回复后再发送文件
     */
public:
    explicit WNCimage(QImage ima=QImage());
    explicit WNCimage(QString username,QTcpSocket * sock,QString fileName="");
    void sendinform_submit_image();
    void sendinform_chatfile_image();
    void send_submit_image();
    void send_chatfile_image(std::vector<std::string>userList);
    void getImagefromdir(QString dir);//从路径名获取image
    QImage image;

private:
    QByteArray getImageData(const QImage &image);
    QString udata;

    QTcpSocket *client;
    QFile *localFile;     // 要发送的文件
    int totalBytes;    // 发送的图片数据的总大小
    qint64 payloadSize;   // 每次发送数据的大小(64k) 未用到
    QString fileName;     // 保存文件路径
    QByteArray outBlock;  // 数据缓冲区，即存放每次要发送的数据块
    QString currentImageName;//图片名
    volatile bool isOk;//连接正常
};

#endif // WNCIMAGE_H
