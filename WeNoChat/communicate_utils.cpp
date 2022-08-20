#include"communicate_utils.h"
std::string Encoder_packdata(std::string info_type,std::string username,std::string info,int state){
    //将发送的信息按json文件的字符串格式编码，输出string
    /*发送信息：
     * - info_type: login/register/... 英文表述的信息类型（需要可添加）
     * - username : 用户名
     * - info     : 信息
     * - state    : 客户端不输入或者输入非0、1的值，没用；服务端输入0-失败，1-成功
     */
    Json::Value json_tmp;
    json_tmp["info_type"]=info_type;
    json_tmp["username"]=username;
    json_tmp["info"]=info;
    json_tmp["state"]=state;
    Json::FastWriter writer;
    std::string strJson = writer.write(json_tmp);
    return strJson;

}

int Decoder_packdata(const std::string packdata,std::string &info_type,std::string &username,std::string &info,int &state){
    //将接收的json格式字符串解码为username及信息
    /*接收信息：
     * - packdata : 接收的json格式字符串
     *解码到下面的变量中
     * - info_type: login/register/... 英文表述的信息类型（需要可添加）
     * - username : 用户名
     * - info     : 信息
     * - state    : 客户端不输入或者输入非0、1的值，没用；服务端输入0-失败，1-成功
     *返回：解码成功-1，解码失败-0
     */
    Json::Reader reader;
    Json::Value json_tmp;

    if (!reader.parse(packdata, json_tmp))
          return 0;

    info_type=json_tmp["info_type"].asString();
    username=json_tmp["username"].asString();
    info=json_tmp["info"].asString();
    state=json_tmp["state"].asInt();
    return 1;
}
