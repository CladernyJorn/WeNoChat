# 服务端

目前实现的功能有：登录，注册，找回密码，加好友，获取好友列表，私聊。

暂不支持头像信息和聊天记录暂存

## 编译

首先运行Server文件夹下的env.sh，安装环境

```shell
sh env.sh
```

在Server文件夹下，运行build.sh

```shell
sh build.sh
```

## 运行

- 我们自己用的（发布的时候删掉）

在Server文件夹下，运行run.sh（这个是调试用的）

```shell
sh run.sh
```

- 发布的

进入Server/bin文件夹，运行Server

```shell
./Server
```

## 数据表

```sql
create table User(
    uName varchar(32) primary key,
    pWord varchar(32) not null,
    phonenum varchar(11) unique not null,
    secureQue int not null,
    secureAns text not null
);

create table Friends(
    username varchar(32) not null,
    friend varchar(32) not null,
    primary key (username, friend),
    foreign key (username) references User(uName),
    foreign key (friend) references User(uName)
);

create trigger drop_user before delete
on User
begin
    delete from Friends where username = old.uName or friend = old.uName;
end;

create trigger add_friends after insert on Friends
begin
    insert into Friends values(new.friend, new.username);
end;

```

## 指令测试：

```json
{
    "type": "regist",
    "info": {
        "username": "jack",
        "password": "123",
        "phonenum": "12345678900",
        "secureQue": 1,
        "secureAns":"fuck"
    }
}

{
    "type": "login",
    "info": {
        "username": "jack",
        "password": "123"
    }
}

{
    "type": "chat",
    "info": {
        "username": "andy",
        "userList": ["jack"],
        "info": "你好"
    }
}

{
    "type": "addfriends",
    "info": {
        "username": "andy",
        "friend_username": "jack"
    }
}

{
    "type": "askfriendsList",
    "info": {
        "username": "andy"
    }
}

{
    "type": "findpWord1",
    "info": {
        "username": "andy",
        "phonenum": "12345678900"
    }
}

{
    "type": "findpWord2",
    "info": {
        "username": "andy",
        "secureAns": "fuck"
    }
}

{
    "type": "findpWord3",
    "info": {
        "username": "andy",
        "newpWord": "123456"
    }
}

{
    "type": "cancelFindpWord",
    "info": {
        "username": "andy",
    }
}