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
int Decoder_login(Json::Value packdata,std::string &username,std::string &info,bool &state);//login解码

//regist
std::string Encoder_regist(std::string username,std::string password,std::string phonenum,int secureQue,std::string secureAns);
int Decoder_regist(Json::Value packdata,std::string &username,std::string &info,bool &state);//regist解码

//chat
std::string Encoder_chat(std::string username,std::string info,std::vector<std::string> userList);
int Decoder_chat(Json::Value packdata,std::string &sender_username,std::string &info);

//addfriends加好友
std::string Encoder_addfriends(std::string username,std::string friend_username);
int Decoder_addfriends(Json::Value packdata,std::string &username,bool &state,std::string &friend_image);

//askfriendsList 请求好友列表
std::string Encoder_askfriendsList(std::string username);
int Decoder_askfriendsList(Json::Value packdata,std::string &username,std::vector<std::string> &userList,std::string &user_image);

//inform_chatfile 发图片前先通知服务器
std::string Encoder_inform_chatfile(std::string filename,std::string username,int size);
int Decoder_ready_chatfile(Json::Value packdata,bool& state);

//chatfile 聊天发送图片
std::string Encoder_chatfile(std::string filename,std::string username,std::vector<std::string>userList,std::string info);
int Decoder_chatfile(Json::Value packdata,std::string &filename,std::string &sender_name,std::string &info);

//inform_submit_image 发图片前先通知服务器
std::string Encoder_inform_submit_image(std::string filename,std::string username,int size);
int Decoder_ready_submit_image(Json::Value packdata,bool& state);

//submit_image上传个人头像
std::string Encoder_submit_image(std::string username,std::string image);
int Decoder_submit_image(Json::Value packdata,std::string &username,bool &state);

//findpWord1
std::string Encoder_findpWord1(std::string username,std::string phonenum);
int Decoder_findpWord1(Json::Value packdata,std::string &username,bool &state,int &secureQue,std::string &info);

//findpWord2
std::string Encoder_findpWord2(std::string username,std::string secureAns);
int Decoder_findpWord2(Json::Value packdata,std::string &username,bool &state);

//findpWord3
std::string Encoder_findpWord3(std::string username,std::string newpWord);
int Decoder_findpWord3(Json::Value packdata,std::string &username,bool &state);
#endif // COMMUNICATE_UTILS_H

