#include "wncimage.h"
//定义了WNCimage类用于打包发送图片，以及单独的解压函数，用于将服务端返回的json解压出Qimage文件

QImage QString2Qimage(const QString &info){
    QByteArray imageData = QByteArray::fromBase64(info.toLatin1());
    QImage image;
    image.loadFromData(imageData);
    return image;
}
WNCimage::WNCimage(QImage ima)
{
    image=ima;
}
WNCimage::WNCimage(QString username,QTcpSocket * sock,QString filename){
    client=sock;
    udata=username;
    payloadSize = 64 * 1024; // 64KB
    totalBytes = 0;
    fileName=filename;
    getImagefromdir(fileName);//根据fileName设置image
    if (!fileName.isEmpty()) {
        //获得实际文件名
        currentImageName = fileName.right(fileName.size()- fileName.lastIndexOf('/')-1);

        //ui->clientStatusLabel->setText(tr("打开 %1 文件成功！").arg(currentImageName));
    }
}

void WNCimage::sendinform_submit_image(){
    if(!isOk)return;
    std::string data=Encoder_inform_submit_image(currentImageName.toStdString() ,udata.toStdString(),totalBytes);
    QString packData = QString::fromStdString(data);
    client->write((packData.toLocal8Bit()));
    qDebug()<<"发送文件请求\n";
}

void WNCimage::send_submit_image(){
    if(!isOk)return;
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_6);
    QString imageData = getImageData(image);

    outBlock.clear();//清空，上面的加载仅仅是为了计算imageData+文件大小的数据量
    //组合json文件:格式为   打包的图片json+总文件大小+json文件大小
    std::string data=Encoder_submit_image(udata.toStdString(),imageData.toStdString());
    QString packData = QString::fromStdString(data);
    sendOut.writeRawData(data.c_str(), packData.length());
    qDebug() << "整个包的大小: " << totalBytes << endl;
    qDebug()<<"发送成功\n";
    outBlock.clear();

}
void WNCimage::sendinform_chatfile_image(){
    if(!isOk)return;
    std::string data=Encoder_inform_chatfile(currentImageName.toStdString() ,udata.toStdString(),totalBytes);
    QString packData = QString::fromStdString(data);
    client->write((packData.toLocal8Bit()));
    qDebug()<<"发送文件请求\n";
}

void WNCimage::send_chatfile_image(std::vector<std::string>userList){
    if(!isOk)return;
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_6);
    QString imageData = getImageData(image);
    // 保留总大小信息空间、图像大小信息空间，然后输入图像信息

    outBlock.clear();//清空，上面的加载仅仅是为了计算imageData+文件大小的数据量
    //组合json文件:格式为   打包的图片json+总文件大小+json文件大小
    std::string data=Encoder_chatfile("image",udata.toStdString(),userList,imageData.toStdString());
    QString packData = QString::fromStdString(data);
    sendOut.writeRawData(data.c_str(), packData.length());
    client->write(outBlock);
    qDebug() << "整个包的大小: " << totalBytes << endl;
    qDebug()<<"发送文件成功\n";
    outBlock.clear();
}

void WNCimage::getImagefromdir(QString dir){
    fileName=dir;
    image=QImage(fileName);

    if (!fileName.isEmpty()) {
        //获得实际文件名
        currentImageName = fileName.right(fileName.size()- fileName.lastIndexOf('/')-1);
        QString cat=currentImageName.right(currentImageName.size()- currentImageName.lastIndexOf(".")-1);
        qDebug()<<"文件类型："<<cat;
        if(cat!="jpg"&&cat!="jpeg"&&cat!="svg"&&cat!="bmp"&&cat!="png"&&cat!="gif"){
            qDebug()<<"文件类型不正确\n";
            isOk=false;
            return;
        }
        //ui->clientStatusLabel->setText(tr("打开 %1 文件成功！").arg(currentImageName));
    }
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_6);
    QString imageData = getImageData(image);
    totalBytes = imageData.length();
    outBlock.clear();
    isOk=true;
}




QByteArray WNCimage::getImageData(const QImage &image)
{
    QByteArray imageData;
    QBuffer buffer(&imageData);
    image.save(&buffer, "png");
    imageData = imageData.toBase64();

    return imageData;
}
