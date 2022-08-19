数据表

```sql
create table User(
    username varchar(32) primary key,
    password varchar(32) not null,
    phonenum varchar(11),
    secureQue int,
    secureAns text
);

create table Friends(
    username varchar(32),
    friend varchar(32),
    primary key (username, friend)
);
```