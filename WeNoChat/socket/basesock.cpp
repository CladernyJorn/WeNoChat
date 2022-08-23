#include "basesock.h"

using namespace std;

BaseSock::BaseSock(QObject *parent) : QObject(parent),onConnected([=](){})
{
    sock = new QTcpSocket();
}

BaseSock::~BaseSock()
{
    sock->disconnectFromHost();
    sock->close();
    delete sock;
}

void BaseSock::connectToHost(const QString &addr, quint16 port,QIODevice::OpenMode mode)
{
    sock->connectToHost(addr,port,mode);
    connect(sock, SIGNAL(connected()), this, SLOT(handConnected()));
}

void BaseSock::addCallback(string cmdType, std::function<void (const Json::Value &)> fun)
{
    _callbacks[cmdType] = fun;
}

quint64 BaseSock::sendMessage(const QString &msg)
{
    return sendMsg(sock, msg.toUtf8());
}

void BaseSock::setConnectCallback(std::function<void()> onConnected)
{
    this->onConnected = onConnected;
}

void BaseSock::handConnected()
{
    onConnected();
    qDebug()<< "connected successed";
    connect(sock, SIGNAL(readyRead()), this, SLOT(handReadyRead()));
}

void BaseSock::handReadyRead()
{
    QByteArray buf = recvMsg(sock);
    Json::Reader reader;
    Json::Value json;

    qDebug()<<"recv = "<<buf;

    if (!reader.parse(buf.toStdString(), json))
    {
        qDebug() << "服务器返回信息错误";
        return;
    }
    if (!json.isObject())
    {
        qDebug() << "服务器返回信息错误";
        return;
    }
    string type = json["type"].asString();
    Json::Value cmd = json["info"];

    auto callback = _callbacks.find(type);
    if(callback!=_callbacks.end())
    {
        callback->second(cmd);
    }
    else
    {
        qDebug()<<"服务器返回信息错误";
    }
}

void BaseSock::abort()
{
    sock->abort();
}
