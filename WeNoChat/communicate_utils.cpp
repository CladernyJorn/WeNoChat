#include"communicate_utils.h"

std::string Encoder(std::string type,Json::Value info){
    //通用编码，info仍是一个json文件，不建议直接使用
    //将发送的信息按json文件的字符串格式编码，输出string
    /*发送信息：
     * - type: login/register/... 英文表述的信息类型（需要可添加）
     * - info     : 信息(仍为一个json文件）
     */
    Json::Value json_tmp;
    json_tmp["type"]=type;
    json_tmp["info"]=info;
    Json::FastWriter writer;
    std::string strJson = writer.write(json_tmp);
    return strJson;
}
//login
std::string Encoder_login(std::string username,std::string pwd){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["password"]=pwd;
    return Encoder("login",jtmp);
}
int Decoder_login(std::string packdata,std::string &username,std::string &info,bool &state){
    //login解码
    /*接收信息：
     * - packdata : 接收的json格式字符串
     *解码到下面的变量中
     * - username : 用户名
     * - info     : 信息
     *返回：解码成功-1，解码失败-0
     */
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="login")return 0;

    tmp_info=jtmp["info"];
    
    username=tmp_info["username"].asString();
    info=tmp_info["info"].asString();
    state=tmp_info["state"].asBool();
    return 1;
}

//regist
std::string Encoder_regist(std::string username,std::string password,std::string phonenum,int secureQue,std::string secureAns){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["password"]=password;
    jtmp["phonenum"]=phonenum;
    jtmp["secureQue"]=secureQue;
    jtmp["secureAns"]=secureAns;
    return Encoder("regist",jtmp);
}
int Decoder_regist(std::string packdata,std::string &username,std::string &info,bool &state){
    //regist解码
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="regist")return 0;
    
    tmp_info=jtmp["info"];
    
    username=tmp_info["username"].asString();
    info=tmp_info["info"].asString();
    state=tmp_info["state"].asBool();
    return 1;
}

//chat
std::string Encoder_chat(std::string username,std::string info,std::vector<std::string> userList){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["info"]=info;
    for(auto user:userList){
        jtmp["userList"].append(user);
    }
    return Encoder("chat",jtmp);
}
int Decoder_chat(std::string packdata,std::string &sender_username,std::string &info){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="chat")return 0;
    
    tmp_info=jtmp["info"];
    
    sender_username=tmp_info["username"].asString();
    info=tmp_info["info"].asString();
    return 1;
}

//addfriends加好友
std::string Encoder_addfriends(std::string username,std::string friend_username){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["friend_username"]=friend_username;
    return Encoder("addfriends",jtmp);
}
int Decoder_addfriends(std::string packdata,std::string &username,bool &state,std::string &friend_image){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="addfriends")return 0;
    
    tmp_info=jtmp["info"];
    
    username=tmp_info["username"].asString();
    state=tmp_info["state"].asBool();
    friend_image=tmp_info["friend_image"].asString();
    return 1;
}

//askfriendsList 请求好友列表
std::string Encoder_askfriendsList(std::string username){
    Json::Value jtmp;
    jtmp["username"]=username;
    return Encoder("askfriendsList",jtmp);
}
int Decoder_askfriendsList(std::string packdata,std::string &username,std::vector<std::string> &userList,std::string &user_image){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="askfriendsList")return 0;
    
    tmp_info=jtmp["info"];
    
    username=tmp_info["username"].asString();
    for(auto user:tmp_info["userList"]){
        userList.push_back(user.asString());
    }
    user_image=tmp_info["user_image"].asString();
    return 1;
}

//inform_chatfile 发图片前先通知服务器
std::string Encoder_inform_chatfile(std::string filename,std::string username,int size){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["filename"]=filename;
    jtmp["size"]=size;
    return Encoder("inform_chatfile",jtmp);
}

int Decoder_ready_chatfile(std::string packdata,bool& state){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="ready_chatfile")return 0;

    tmp_info=jtmp["info"];

    state=tmp_info["state"].asBool();
    return 1;
}

//chatfile发送文件
std::string Encoder_chatfile(std::string type,std::string username,std::vector<std::string>userList,std::string info){
    Json::Value jtmp;
    jtmp["username"]=username;
    for(auto user:userList){
        jtmp["userList"].append(user);
    }
    jtmp["type"]=type;
    jtmp["info"]=info;
    return Encoder("chatfile",jtmp);
}
int Decoder_chatfile(std::string packdata,std::string &filename,std::string &sender_name,std::string &info){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="chatfile")return 0;

    tmp_info=jtmp["info"];

    sender_name=tmp_info["username"].asString();
    filename=tmp_info["filename"].asString();
    info=tmp_info["info"].asString();
    return 1;
}

//inform_submit_image 发图片前先通知服务器
std::string Encoder_inform_submit_image(std::string filename,std::string username,int size){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["filename"]=filename;
    jtmp["size"]=size;
    return Encoder("inform_submit_image",jtmp);
}

int Decoder_ready_submit_image(std::string packdata,bool& state){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="ready_submit_image")return 0;

    tmp_info=jtmp["info"];

    state=tmp_info["state"].asBool();
    return 1;
}

//submit_image上传个人头像
std::string Encoder_submit_image(std::string username,std::string image){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["image"]=image;
    return Encoder("submit_image",jtmp);
}
int Decoder_submit_image(std::string packdata,std::string &username,bool &state){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="submit_image")return 0;

    tmp_info=jtmp["info"];

    username=tmp_info["username"].asString();
    state=tmp_info["state"].asBool();
    return 1;
}

//findpWord1
std::string Encoder_findpWord1(std::string username,std::string phonenum){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["phonenum"]=phonenum;
    return Encoder("findpWord1",jtmp);
}
int Decoder_findpWord1(std::string packdata,std::string &username,bool &state,int &secureQue,std::string &info){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="findpWord1")return 0;
    
    tmp_info=jtmp["info"];
    
    username=tmp_info["username"].asString();
    state=tmp_info["state"].asBool();
    secureQue=tmp_info["secureQue"].asInt();
    info=tmp_info["info"].asString();
    return 1;
}

//findpWord2
std::string Encoder_findpWord2(std::string username,std::string secureAns){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["secureAns"]=secureAns;
    return Encoder("findpWord2",jtmp);
}
int Decoder_findpWord2(std::string packdata,std::string &username,bool &state){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="findpWord2")return 0;
    
    tmp_info=jtmp["info"];
    
    username=tmp_info["username"].asString();
    state=tmp_info["state"].asBool();
    return 1;
}

//findpWord3
std::string Encoder_findpWord3(std::string username,std::string newpWord){
    Json::Value jtmp;
    jtmp["username"]=username;
    jtmp["newpWord"]=newpWord;
    return Encoder("findpWord3",jtmp);
}
int Decoder_findpWord3(std::string packdata,std::string &username,bool &state){
    Json::Reader reader;
    Json::Value jtmp,tmp_info;

    if (!reader.parse(packdata, jtmp))return 0;
    if(jtmp["type"].asString()!="findpWord3")return 0;
    
    tmp_info=jtmp["info"];
    
    username=tmp_info["username"].asString();
    state=tmp_info["state"].asBool();
    return 1;
}
