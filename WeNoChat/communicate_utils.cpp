#include "communicate_utils.h"
#include "wncimage.h"
std::string Encoder(std::string type, Json::Value info)
{
    //通用编码，info仍是一个json文件，不建议直接使用
    //将发送的信息按json文件的字符串格式编码，输出string
    /*发送信息：
     * - type: login/register/... 英文表述的信息类型（需要可添加）
     * - info     : 信息(仍为一个json文件）
     */
    Json::Value json_tmp;
    json_tmp["type"] = type;
    json_tmp["info"] = info;
    Json::FastWriter writer;
    std::string strJson = writer.write(json_tmp);
    return strJson;
}
// login
std::string Encoder_login(std::string username, std::string pwd)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["password"] = pwd;
    return Encoder("login", jtmp);
}
int Decoder_login(Json::Value packdata, std::string &username, std::string &info, bool &state)
{
    // login解码
    /*接收信息：
     * - packdata : 接收的json格式字符串
     *解码到下面的变量中
     * - username : 用户名
     * - info     : 信息
     *返回：解码成功-1，解码失败-0
     */

    if (!packdata.isObject())
        return 0;

    username = packdata["username"].asString();
    info = packdata["info"].asString();
    state = packdata["state"].asBool();
    return 1;
}

// regist
std::string Encoder_regist(std::string username, std::string password, std::string phonenum, int secureQue, std::string secureAns)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["password"] = password;
    jtmp["phonenum"] = phonenum;
    jtmp["secureQue"] = secureQue;
    jtmp["secureAns"] = secureAns;
    return Encoder("regist", jtmp);
}
int Decoder_regist(Json::Value packdata, std::string &username, std::string &info, bool &state)
{
    // regist解码

    if (!packdata.isObject())
        return 0;

    username = packdata["username"].asString();
    info = packdata["info"].asString();
    state = packdata["state"].asBool();
    return 1;
}

// chat
std::string Encoder_chat(std::string username, std::string info, std::vector<std::string> userList)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["info"] = info;
    for (auto user : userList)
    {
        jtmp["userList"].append(user);
    }
    return Encoder("chat", jtmp);
}
int Decoder_chat(Json::Value packdata, std::string &sender_username, std::string &info)
{

    if (!packdata.isObject())
        return 0;

    sender_username = packdata["username"].asString();
    info = packdata["info"].asString();
    return 1;
}

// addfriends加好友
std::string Encoder_addfriends(std::string username, std::string friend_username)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["friend_username"] = friend_username;
    return Encoder("addfriends", jtmp);
}
int Decoder_addfriends(Json::Value packdata, std::string &username, bool &state, std::string &friend_image)
{

    if (!packdata.isObject())
        return 0;

    username = packdata["username"].asString();
    state = packdata["state"].asBool();
    friend_image = packdata["friend_image"].asString();
    return 1;
}

// askfriendsList 请求好友列表
std::string Encoder_askfriendsList(std::string username)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    return Encoder("askfriendsList", jtmp);
}
int Decoder_askfriendsList(Json::Value packdata, std::string &username, std::vector<Ui::User> &user_info_List, std::string &user_image)
{
    if (!packdata.isObject())
        return 0;
    username = packdata["username"].asString();
    user_image = packdata["user_image"].asString();

    for (auto user_info : packdata["user_info_List"])
    {
        Ui::User friend_info;
        friend_info.image = QString2Qimage(QString::fromStdString(user_info["friend_image"].asString()));
        friend_info.userName = user_info["friend_name"].asString();
        user_info_List.push_back(friend_info);
    }

    return 1;
}

// inform_chatfile 发图片前先通知服务器
std::string Encoder_inform_chatfile(std::string filename, std::string username, int size)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["filename"] = filename;
    jtmp["size"] = size;
    return Encoder("inform_chatfile", jtmp);
}

int Decoder_ready_chatfile(Json::Value packdata, bool &state)
{

    if (!packdata.isObject())
        return 0;

    state = packdata["state"].asBool();
    return 1;
}

// chatfile发送文件
std::string Encoder_chatfile(std::string filename, std::string username, std::vector<std::string> userList, std::string info)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    for (auto user : userList)
    {
        jtmp["userList"].append(user);
    }
    jtmp["filename"] = filename;
    jtmp["info"] = info;
    return Encoder("chatfile", jtmp);
}
int Decoder_chatfile(Json::Value packdata, std::string &filename, std::string &sender_name, std::string &info)
{

    qDebug() << "chatfile recv = " << QString::fromStdString(Json::FastWriter().write(packdata));
    if (!packdata.isObject())
        return 0;

    sender_name = packdata["username"].asString();
    filename = packdata["filename"].asString();
    info = packdata["info"].asString();
    return 1;
}

// inform_submit_image 发图片前先通知服务器
std::string Encoder_inform_submit_image(std::string filename, std::string username, int size)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["filename"] = filename;
    jtmp["size"] = size;
    return Encoder("inform_submit_image", jtmp);
}

int Decoder_ready_submit_image(Json::Value packdata, bool &state)
{

    if (!packdata.isObject())
        return 0;

    state = packdata["state"].asBool();
    return 1;
}

// submit_image上传个人头像
std::string Encoder_submit_image(std::string username, std::string image)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["image"] = image;
    return Encoder("submit_image", jtmp);
}
int Decoder_submit_image(Json::Value packdata, std::string &username, bool &state)
{

    if (!packdata.isObject())
        return 0;

    username = packdata["username"].asString();
    state = packdata["state"].asBool();
    return 1;
}

// findpWord1
std::string Encoder_findpWord1(std::string username, std::string phonenum)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["phonenum"] = phonenum;
    return Encoder("findpWord1", jtmp);
}
int Decoder_findpWord1(Json::Value packdata, std::string &username, bool &state, int &secureQue, std::string &info)
{

    if (!packdata.isObject())
        return 0;

    username = packdata["username"].asString();
    state = packdata["state"].asBool();
    secureQue = packdata["secureQue"].asInt();
    info = packdata["info"].asString();
    return 1;
}

// findpWord2
std::string Encoder_findpWord2(std::string username, std::string secureAns)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["secureAns"] = secureAns;
    return Encoder("findpWord2", jtmp);
}
int Decoder_findpWord2(Json::Value packdata, std::string &username, bool &state)
{

    if (!packdata.isObject())
        return 0;

    username = packdata["username"].asString();
    state = packdata["state"].asBool();
    return 1;
}

// findpWord3
std::string Encoder_findpWord3(std::string username, std::string newpWord)
{
    Json::Value jtmp;
    jtmp["username"] = username;
    jtmp["newpWord"] = newpWord;
    return Encoder("findpWord3", jtmp);
}
int Decoder_findpWord3(Json::Value packdata, std::string &username, bool &state)
{

    if (!packdata.isObject())
        return 0;

    username = packdata["username"].asString();
    state = packdata["state"].asBool();
    return 1;
}
