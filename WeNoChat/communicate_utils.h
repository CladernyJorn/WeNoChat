#ifndef COMMUNICATE_UTILS_H
#define COMMUNICATE_UTILS_H
#include <QWidget>
#include<QDebug>
#include<QMessageBox>
#include<QTcpSocket>
#include"json/json.h"
#include<cstring>
#include<string>
#include<iostream>
#include<vector>
std::string Encoder(std::string type,Json::Value info);//将发送的信息按json文件的字符串格式编码，输出string

//login
std::string Encoder_login(std::string username,std::string pwd);//login编码
int Decoder_login(std::string packdata,std::string &username,std::string &info,bool &state);//login解码

//regist
std::string Encoder_regist(std::string username,std::string password,std::string phonenum,int secureQue,std::string secureAns);
int Decoder_regist(std::string packdata,std::string &username,std::string &info,bool &state);//regist解码

//chat
std::string Encoder_chat(std::string username,std::string info,std::vector<std::string> userList);
int Decoder_chat(std::string packdata,std::string &sender_username,std::string &info);

//addfriends加好友
std::string Encoder_addfriends(std::string username,std::string friend_username);
int Decoder_addfriends(std::string packdata,std::string &username,bool &state);

//askfriendsList 请求好友列表
std::string Encoder_askfriendsList(std::string username);
int Decoder_askfriendsList(std::string packdata,std::string &username,std::vector<std::string> userList);

//findpWord1
std::string Encoder_findpWord1(std::string username,std::string phonenum);
int Decoder_findpWord1(std::string packdata,std::string &username,bool &state,int &secureQue,std::string &info);

//findpWord2
std::string Encoder_findpWord2(std::string username,std::string secureAns);
int Decoder_findpWord2(std::string packdata,std::string &username,bool &state);

//findpWord3
std::string Encoder_findpWord3(std::string username,std::string newpWord);
int Decoder_findpWord3(std::string packdata,std::string &username,bool &state);
#endif // COMMUNICATE_UTILS_H

