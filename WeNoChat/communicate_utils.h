#ifndef COMMUNICATE_UTILS_H
#define COMMUNICATE_UTILS_H
#include <QWidget>
#include<QDebug>
#include<QMessageBox>
#include<QTcpSocket>
#include"json/json.h"
#include<cstring>
#include<iostream>
std::string Encoder_packdata(std::string info_type,std::string username,std::string info,int state=2);//将发送的信息按json文件的字符串格式编码，输出string
int Decoder_packdata(std::string packdata,std::string &info_type,std::string &username,std::string &info,int &state);//将接收的json格式字符串解码为username及信息
#endif // COMMUNICATE_UTILS_H
