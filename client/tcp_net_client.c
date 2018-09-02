#include "tcp_net_socket.h"  
  
struct send  
{  
    char name[20];              //名字  
    char toname[20];            //接收人  
    char account[20];           //账号  
    char passward[20];          //密码  
    int  likes;                 //点赞数  
    int  vip;                   //是否是会员  
    char moto[30];              //个性签名  
    int  cmd;                   //提取操作符  
    char msg[200];              //发送、接收消息  
    char file_name[20];         //文件名  
    char file[2048];            //发送文件存的数据  
    char question[50];          //密保问题  
    char answer[50];            //密保答案  
    char e_s;                   //确认发送的表情  
    char p_s;                   //确认发送的常用语  
};  
  
struct recv  
{  
    char from_name[20];         //发信人  
    char to_name[20];           //名字  
    int  result;                //返回操作结果  
    int  online_num;            //在线人数  
    char num[20][20];           //在线人名  
    char msg[200];              //发送、接收消息  
    char file_name[20];         //文件名  
    char file[2048];            //发送文件存的数据  
    char question[50];          //密保问题  
    char answer[50];            //密保答案  
    char passward[20];          //密码  
    char moto[30];              //个性签名  
    int  likes;                 //点赞数  
    int  vip;                   //是否是会员  
    char e_s;                   //确认发送的表情  
    char p_s;                   //确认发送的常用语  
};  
  
  
struct send userInfo;  
struct recv userBack;  
int ret;  
char fan[20];            //输入任意键返回  
char Name[20];  
int READEN = 0;  
int State;  
int LIKES = 0;  
int OUT = 0;  
  
//主界面显示  
void show()  
{  
    system("clear");  
    printf("\n\n\n");  
    printf("\t\t\t\t  欢迎来到聊天室!祝您聊天愉快！");  
    printf("\n\n\n\n\n");  
    printf("\t\t\t\t\t1  注册\n");  
    printf("\t\t\t\t\t2  登录\n");  
    printf("\t\t\t\t\t3  忘记密码\n");  
    printf("\t\t\t\t\t4  退出\n");  
    printf("\n\n\t\t\t请输入选择：");  
}  
  
//注册界面显示及处理  
int show_reg()  
{  
    char pass1[20];  
    char pass2[20];  
    char temp;  
    int i = 0;  
    int j = 0;  
    system("clear");  
    printf("\n\n\n\n");  
    State = 0;                  //禁言标志位  
    userInfo.cmd = reg;  
    userInfo.likes = 0;  
    userInfo.vip = 0;  
    printf("\t\t\t\t请输入账号：");  
    scanf("%s",userInfo.account);  
      
    printf("\n\t\t\t\t请输入密码：");  
      
    while(i < 20)  
    {  
        pass1[i] = mygetch();  
        if(pass1[i] == 10)  
        {  
            if(j == 0)                  ////防止输入账号的最后一个回车影响   
            {     
                j++;  
                continue;  
            }  
            break;  
        }  
        printf("*");  
        i++;  
    }  
    pass1[i] = '\0';  
      
    i = 0;  
    printf("\n\n\t\t\t\t请确认您的密码：");  
    while(i < 20)  
    {  
        pass2[i] = mygetch();  
        if(pass2[i] == 10)  
        {  
            break;  
        }  
        printf("*");  
        i++;  
    }  
    pass2[i] = '\0';  
      
    printf("\n\n\t\t\t\t请设计您的昵称：");  
    scanf("%s",userInfo.name);  
      
    strcpy(userInfo.moto, "我想回家(T_T)");  
      
    printf("\n\n\t\t\t\t请输入密保问题：");  
    scanf("%s",userInfo.question);  
    SCAN_N();  
      
    printf("\n\n\t\t\t\t请输入密保答案：");  
    scanf("%s",userInfo.answer);  
    SCAN_N();  
      
    system("clear");  
    printf("\n\n\n\n\n\n\n\t\t\t正在注册......\n");  
    sleep(2);  
      
    if(strcmp(pass1, pass2) != 0)  
    {  
        printf("\n\n\t\t\t\t密码输入有误！请重新注册！\n");  
        printf("\n\n\n\t\t输入ENTER键返回：");  
        fgets(fan, 20, stdin);  
        return -9;  
    }  
    else  
    {  
        strcpy(userInfo.passward, pass1);  
    }  
}  
  
//登录界面显示  
int show_log()  
{  
    char pass1[20];  
    int i = 0;  
    int j = 0;  
    system("clear");  
    printf("\n\n\n\n\n\n\n");  
    printf("\t\t\t\t请输入账号：");  
    scanf("%s",userInfo.account);  
      
    printf("\n\t\t\t\t请输入密码：");  
      
    while(i < 20)  
    {  
        pass1[i] = mygetch();  
        if(pass1[i] == 10)  
        {  
            if(j == 0)                  ////防止输入账号的最后一个回车影响   
            {     
                j++;  
                continue;  
            }  
            break;  
        }  
        printf("*");  
        i++;  
    }  
    pass1[i] = '\0';  
      
    strcpy(userInfo.passward, pass1);  
      
    system("clear");  
    printf("\n\n\n\n\n\n\n\t\t\t正在登陆......\n");  
    sleep(2);  
}  
  
//登陆之后界面显示及处理  
int show_chat()  
{  
    system("clear");  
    gettime();  
    printf("\n%s   个性签名：%s   点赞数：%d", Name, userBack.moto, LIKES);  
    if(userBack.vip == 1)  
    {  
        printf("\t\t尊贵的黄金会员");  
    }  
    else  
    {  
        printf("\t\t普通用户");  
    }  
    printf("\n\n\t\t\t\t\t a 私聊\n");  
    printf("\t\t\t\t\t b 群聊\n");  
    printf("\t\t\t\t\t c 文件传输\n");  
    printf("\t\t\t\t\t d 查看在线人数\n");  
    printf("\t\t\t\t\t e 发送表情\n");  
    printf("\t\t\t\t\t f 常用语\n");  
    printf("\t\t\t\t\t g 点赞\n");  
    printf("\t\t\t\t\t h 更改个性签名\n");  
    printf("\t\t\t\t\t i 注册会员\n");  
    printf("\t\t\t\t\t j 禁言(需开通会员)\n");  
    printf("\t\t\t\t\t k 解禁(需开通会员)\n");  
    printf("\t\t\t\t\t l 踢人(需开通会员)\n");  
    printf("\t\t\t\t\t m 查看聊天记录\n");  
    printf("\t\t\t\t\t n 退出\n");  
    printf("\n\t\t请输入您的选择：");  
}  
  
//文件传输发送  
int deal_sendfile(int sfd)  
{  
    char bs;  
    int ret;  
    int fd;  
    ssize_t num;  
    int i = 0;  
      
    system("clear");  
    printf("\n\n\n\n");  
      
    if(State == Shutup)  
    {  
        printf("\n\n\n\n\t\t您处于被禁言状态！无法发言！开通会员可以解禁`(*∩_∩*)′\n");  
        printf("\n\n\n\t\t输入ENTER键返回：");  
        fgets(fan, 20, stdin);  
        return Shutup;  
    }  
      
    printf("\n\t\t\t您想给谁发文件呢？：");  
    scanf("%s", userInfo.toname);  
      
    strcpy(userInfo.name, Name);      
      
    printf("\n\n\t\t\t请告诉我本文件夹下要发送的文件名`(*∩_∩*)′：");  
    scanf("%s", userInfo.file_name);  
    SCAN_N();  
      
    userInfo.cmd = file_transfer;  
      
    if(strcmp(Name, userInfo.toname) == 0)  
    {  
        sleep(1);  
        system("clear");  
        printf("\n\n\n\n\n\n\t\t不可以给自己发送文件哦`(*∩_∩*)′");  
        printf("\n\n\n\t\t输入ENTER键返回：");  
        fgets(fan, 20, stdin);  
        return -1;  
    }  
      
    fd = open(userInfo.file_name, O_RDONLY, S_IRUSR | S_IWUSR);  
    if(fd < 0)  
    {  
        printf("\n\n\t\t\t\t没有此文件！\n");  
        printf("\n\n\n\t\t输入ENTER键返回：");  
        fgets(fan, 20, stdin);  
        return -1;  
    }  
      
    while(1)  
    {  
        memset(&bs, 0, sizeof(bs));  
        ssize_t read_bytes = read(fd, &bs, sizeof(bs));  
        if(read_bytes == -1)  
        {  
            perror("read");  
            return -1;  
        }  
        if(read_bytes == 0)  
        {  
            break;  
        }  
        userInfo.file[i] = bs;  
        i++;  
    }  
    userInfo.file[i] = '\0';  
      
    ret = write(sfd, &userInfo,sizeof(userInfo));  
    if(ret == -1)  
    {  
        perror("write");  
        return -1;  
    }  
      
    printf("\n\n\t\t\t正在发送...\n");  
    sleep(2);  
}  
  
//收文件  
int back_file()  
{  
    system("clear");  
    printf("\n\n\n\n\t\t%s用户发送了一份文件给您，请确认接收！\n", userBack.from_name);  
    sleep(2);  
      
    int fd;  
    fd = open(userBack.file_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);  
    if(fd < 0)  
    {  
        perror("open");  
        return -1;  
    }  
      
    ret = write(fd, userBack.file, strlen(userBack.file));  
    if(ret == -1)  
    {  
        perror("write");  
        return -1;  
    }  
      
    printf("\n\n\t\t恭喜您接收文件成功！`(*∩_∩*)′");  
    printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
}  
  
//发送表情选择  
int deal_send_expr(int sfd)  
{  
    char e[10];     //输入表情选项  
      
    system("clear");  
    printf("\n\n\n\n");  
    if(State == Shutup)  
    {  
        printf("\n\n\n\n\t\t您处于被禁言状态！无法发言！开通会员可以解禁`(*∩_∩*)′\n");  
        printf("\n\n\n\t\t输入ENTER键返回：");  
        fgets(fan, 20, stdin);  
        return Shutup;  
    }  
      
    printf("\n\t\t\t您想发表情给谁呢？：");  
    scanf("%s", userInfo.toname);  
    strcpy(userInfo.name, Name);  
    userInfo.cmd = expression;  
      
    printf("\n\n\t\t\t\t1 开心       :-D\n");  
    printf("\t\t\t\t2 生气       ＝　＝＃\n");  
    printf("\t\t\t\t3 为你加油   *\(^_^)/*\n");  
    printf("\t\t\t\t4 两手一摊   ╮(￣▽ ￣)╭\n");  
    printf("\t\t\t\t5 飞吻       づ￣ 3￣)づ\n");  
    printf("\t\t\t\t6 哭泣       (T_T)\n");  
    printf("\t\t\t\t7 竖起大拇指 b（￣▽￣）d\n");  
    printf("\t\t\t\t8 不满       (︶︿︶)\n");  
    printf("\t\t\t\t9 亲亲       >3<\n\n");  
    printf("\t\t请输入您想发送的表情：");  
    scanf("%s", e);  
    SCAN_N();  
      
    userInfo.e_s = e[0];  
      
    if(strcmp(Name, userInfo.toname) == 0)  
    {  
        sleep(1);  
        system("clear");  
        printf("\n\n\n\n\n\n\t\t不可以给自己发送表情哦`(*∩_∩*)′");  
        printf("\n\n\n\t\t输入ENTER键返回：");  
        fgets(fan, 20, stdin);  
        return -1;  
    }  
      
    ret = write(sfd, &userInfo, sizeof(userInfo));  
    if(ret == -1)  
    {  
        perror("write");  
        return -1;  
    }  
    system("clear");  
    printf("\n\n\n\n\n\n\t\t正在发送...\n");  
    sleep(2);  
}  
  
//接受表情信号分析  
int back_ep()  
{  
    char er[20];  
    switch (userBack.e_s)  
    {  
        case '1' :  
        {  
            strcpy(er, ":-D");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一个表情给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",er);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '2' :  
        {  
            strcpy(er, "＝　＝＃");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一个表情给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",er);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '3' :  
        {  
            strcpy(er, "*\(^_^)/*");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一个表情给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",er);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '4' :  
        {  
            strcpy(er, "╮(￣▽ ￣)╭");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一个表情给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",er);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '5' :  
        {  
            strcpy(er, "づ￣ 3￣)づ");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一个表情给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",er);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '6' :  
        {  
            strcpy(er, "(T_T)");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一个表情给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",er);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '7' :  
        {  
            strcpy(er, "b（￣▽￣）d");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一个表情给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",er);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '8' :  
        {  
            strcpy(er, "(︶︿︶)");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一个表情给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",er);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '9' :  
        {  
            strcpy(er, ">3<");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一个表情给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",er);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        default :  
        {  
            system("clear");  
            printf("\n\n\n\n\t\t抱歉！输入错误！/n");  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
    }  
}  
  
//发送常用语选择  
int deal_phrases(int sfd)  
{  
    char p[10];                 //输入常用语选项  
      
    system("clear");  
    printf("\n\n\n\n");  
    if(State == Shutup)  
    {  
        printf("\n\n\n\n\t\t您处于被禁言状态！无法发言！开通会员可以解禁`(*∩_∩*)′\n");  
        printf("\n\n\n\t\t输入ENTER键返回：");  
        fgets(fan, 20, stdin);  
        return Shutup;  
    }  
      
    printf("\n\t\t\t您想给谁发信息呢？：");  
    scanf("%s", userInfo.toname);  
    strcpy(userInfo.name, Name);              
    userInfo.cmd = phrases;                   
      
    printf("\n\t\t\t1 はじめまして            (  初次见面 )\n");  
    printf("\t\t\t2 どうぞよろしく          (  请多关照 )\n");  
    printf("\t\t\t3 そうですか              (  是吗？   )\n");  
    printf("\t\t\t4 はい                    (  是的     )\n");  
    printf("\t\t\t5 よくいらっしゃいました  (欢迎，欢迎 )\n");  
    printf("\t\t\t6 どういたしまして        (  不用客气 )\n");  
    printf("\t\t\t7 おはよございます        (   早上好  )\n");  
    printf("\t\t\t8 こんにちは              (  你好！   )\n");  
    printf("\t\t\t9 こんばんは              (   晚上好！)\n");  
    printf("\n\t\t请输入您想发送的常用语：");  
    scanf("%s", p);  
    SCAN_N();  
      
    userInfo.p_s = p[0];  
      
    if(strcmp(Name, userInfo.toname) == 0)  
    {  
        sleep(1);  
        system("clear");  
        printf("\n\n\n\n\n\n\t\t不可以给自己发送常用语哦`(*∩_∩*)′");  
        printf("\n\n\n\t\t输入ENTER键返回：");  
        fgets(fan, 20, stdin);  
        return -1;  
    }  
      
    ret = write(sfd, &userInfo, sizeof(userInfo));  
    if(ret == -1)  
    {  
        perror("write");  
        return -1;  
    }  
    system("clear");  
    printf("\n\n\n\n\n\n\t\t正在发送...\n");  
    sleep(2);  
}  
  
//接受常用语  
int back_ph()  
{  
    char ph[60];  
    switch (userBack.p_s)  
    {  
        case '1' :  
        {     
            strcpy(ph, "はじめまして  ( 初次见面 )");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一句话给您！", userBack.from_name);  
            printf("\n\n\t\t%s\n",ph);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '2' :  
        {  
            strcpy(ph, "どうぞよろしく  ( 请多关照 )");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一句话给您！", userBack.from_name);  
            printf("\n\n\n\t\t%s\n",ph);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '3' :  
        {  
            strcpy(ph, "そうですか    ( 是吗？)");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一句话给您！", userBack.from_name);  
            printf("\n\n\n\t\t%s\n",ph);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '4' :  
        {  
            strcpy(ph, "はい    ( 是的 )");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一句话给您！", userBack.from_name);  
            printf("\n\n\n\t\t%s\n",ph);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '5' :  
        {  
            strcpy(ph, "よくいらっしゃいました  ( 欢迎，欢迎 )");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一句话给您！", userBack.from_name);  
            printf("\n\n\n\t\t%s\n",ph);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '6' :  
        {  
            strcpy(ph, "どういたしまして    ( 不用客气 )");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一句话给您！", userBack.from_name);  
            printf("\n\n\n\t\t%s\n",ph);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '7' :  
        {  
            strcpy(ph, "おはよございます   ( 早上好 )");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一句话给您！", userBack.from_name);  
            printf("\n\n\n\t\t%s\n",ph);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '8' :  
        {  
            strcpy(ph, "こんにちは   ( 你好！)");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一句话给您！", userBack.from_name);  
            printf("\n\n\n\t\t%s\n",ph);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        case '9' :  
        {  
            strcpy(ph, "こんばんは   ( 晚上好！)");  
            system("clear");  
            printf("\n\n\n\n\t\t%s用户发送了一句话给您！", userBack.from_name);  
            printf("\n\n\n\t\t%s\n",ph);  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
        default :  
        {  
            system("clear");  
            printf("\n\n\n\n\t\t抱歉！输入错误！/n");  
            printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
            break;  
        }  
    }  
}  
  
//读线程  
void* Read_from_server(int sfd)  
{  
    int i;  
    while(1)  
    {      
        ret = read(sfd, &userBack, sizeof(userBack));  
        if(ret == -1)  
        {  
            perror("read");  
            return;  
        }  
        READEN = 1;  
        switch (userBack.result)  
        {  
            case (private_chat):  
            {  
                system("clear");  
                printf("\n\n\n\n\n\n\t\t%s 对您说了一句悄悄话：%s",userBack.from_name, userBack.msg);  
                printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
                memset(&userBack.result, 0, sizeof(userBack.result));  
                break;  
            }  
            case (group_chat):  
            {  
                system("clear");  
                printf("\n\n\n\n\t\t%s用户发送了一条信息：%s\n", userBack.from_name, userBack.msg);  
                printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
                memset(&userBack.result, 0, sizeof(userBack.result));  
                break;  
            }  
            case (online_member):  
            {  
                system("clear");  
                printf("\n\n\n\n\t\t当前在线人数：%d\n", userBack.online_num);  
                for(i = 0; i < userBack.online_num; i++)  
                {  
                    printf("\n\n\t\t%s\n",userBack.num[i]);  
                }  
                printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
                memset(&userBack.result, 0, sizeof(userBack.result));  
                break;  
            }  
            case (file_transfer):  
            {  
                back_file();  
                memset(&userBack.result, 0, sizeof(userBack.result));  
                break;  
            }  
            case (expression):  
            {  
                back_ep();  
                memset(&userBack.result, 0, sizeof(userBack.result));  
                break;  
            }  
            case (phrases):  
            {  
                back_ph();  
                memset(&userBack.result, 0, sizeof(userBack.result));  
                break;  
            }  
            case (like):  
            {  
                LIKES = userBack.likes;  
                system("clear");  
                printf("\n\n\n\n\n\n\t\t%s用户给你点了一个赞！`(*∩_∩*)′\n", userBack.from_name);  
                printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
                memset(&userBack.result, 0, sizeof(userBack.result));  
                break;  
            }  
            case (Shutup):  
            {  
                State = Shutup;  
                system("clear");  
                printf("\n\n\n\n\n\n\t\t%s用户把您禁言了！开通会员可以解禁并反击他哦`(*∩_∩*)′\n", userBack.from_name);  
                printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
                memset(&userBack.result, 0, sizeof(userBack.result));  
                break;  
            }  
            case (kick):  
            {  
                OUT = 1;  
                system("clear");  
                printf("\n\n\n\n\n\n\t\t很抱歉，您已被%s用户强制下线！开会员可以把他踢下去哦！`(*∩_∩*)′\n",userBack.from_name);  
                printf("\n\n\n\n\t\t输入ENTER键返回`(*∩_∩*)′\n");  
                memset(&userBack.result, 0, sizeof(userBack.result));  
                break;  
            }  
        }  
    }  
}  
  
//处理登录后的请求  
int deal_log(int sfd)  
{  
    char ecf[12];                        //输入选择  
    char x[2];                           //用于支付确认    
    char xzf[40];                       //聊天文本名字  
    char czf[2048];                     //聊天记录  
      
    while(1)  
    {  
        if(READEN == 1)  
        {  
            READEN = 0;  
            switch(userBack.result)  
            {  
                case (Send_success):  
                {  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t发送成功！\n");  
                    memset(&userBack.result, 0, sizeof(userBack.result));  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                case (like_success):  
                {  
                    system("clear");  
                    printf("\n\n\n\n");  
                    printf("\n\n\t\t恭喜您点赞成功！`(*∩_∩*)′\n");  
                    memset(&userBack.result, 0, sizeof(userBack.result));  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                case (change_success):  
                {  
                    system("clear");  
                    printf("\n\n\n\n");  
                    printf("\n\n\t\t恭喜您更改个性签名成功！`(*∩_∩*)′\n");  
                    memset(&userBack.result, 0, sizeof(userBack.result));  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }   
                case (vip_success):  
                {  
                    system("clear");  
                    printf("\n\n\n\n");  
                    printf("\n\n\t\t恭喜您成为尊贵的黄金会员！`(*∩_∩*)′\n");  
                    memset(&userBack.result, 0, sizeof(userBack.result));  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                case (Shutup_success):  
                {  
                    system("clear");  
                    printf("\n\n\n\n");  
                    printf("\n\n\t\t恭喜您对方已成功被您禁言！`(*∩_∩*)′\n");  
                    memset(&userBack.result, 0, sizeof(userBack.result));  
                    printf("\n\n\n\t\t输入ENTER键离开：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                case (kick_success):  
                {  
                    system("clear");  
                    printf("\n\n\n\n");  
                    printf("\n\n\t\t恭喜您对方已成功被您踢下线！`(*∩_∩*)′\n");  
                    memset(&userBack.result, 0, sizeof(userBack.result));  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                case (Send_error):  
                {  
                    system("clear");  
                    printf("\n\n\n\n");  
                    printf("\n\n\t\t对不起，对方暂时没有登录！\n");  
                    memset(&userBack.result, 0, sizeof(userBack.result));  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
            }  
        }  
              
        show_chat();  
          
        fgets(ecf, 12, stdin);  
          
        if(OUT == 1)  
        {  
            OUT--;  
            return Exit;   
        }  
          
        switch(ecf[0])  
        {  
            case 'a':                   //私聊  
            {  
                int fd1;  
                system("clear");  
                printf("\n\n\n\n");  
                if(State == Shutup)  
                {  
                    printf("\n\n\n\n\t\t您处于被禁言状态！无法发言！开通会员可以解禁`(*∩_∩*)′\n");  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                  
                memset(czf,0,strlen(czf));  
                memset(xzf,0,strlen(xzf));  
                  
                printf("\t\t\t您想和谁聊天呢？请输入对方名字：");  
                scanf("%s", userInfo.toname);  
                SCAN_N();  
  
                printf("\n\n\t\t\t请输入您想要说的话：");  
                scanf("%[^\n]", userInfo.msg);  
                SCAN_N();  
                  
                userInfo.cmd = private_chat;  
                  
                strcpy(userInfo.name,Name);  
                  
                if(strcmp(Name, userInfo.toname) == 0)  
                {  
                    sleep(1);  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t不可以给自己发信息哦`(*∩_∩*)′");  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                  
                ret = write(sfd, &userInfo,sizeof(userInfo));  
                if(ret == -1)  
                {  
                    perror("write");  
                    return -1;  
                }  
                  
                sprintf(xzf, "%s与%s的聊天记录.txt", Name, userInfo.toname);  
                fd1 = open(xzf, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);  
                if(fd1 == -1)  
                {  
                    perror("open");  
                    return -1;  
                }  
                  
                sprintf(czf, "%s 对 %s 发送了一句悄悄话：%s\t%s", Name, userInfo.toname, userInfo.msg,nowtime());  
                ret = write(fd1, czf, strlen(czf));  
                if(ret == -1)  
                {  
                    perror("write");  
                    return -1;  
                }  
                printf("\n\n\t\t\t正在发送...\n");  
                sleep(2);  
                  
                break;  
            }  
            case 'b':                   //群聊  
            {  
                system("clear");  
                printf("\n\n\n\n");  
                int i = 0;  
                  
                if(State == Shutup)  
                {  
                    printf("\n\n\n\n\t\t您处于被禁言状态！无法发言！开通会员可以解禁`(*∩_∩*)′\n");  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                  
                printf("\n\n\n\n\n\t\t\t请输入您想要说的话：");  
                scanf("%[^\n]", userInfo.msg);  
                SCAN_N();  
                  
                userInfo.cmd = group_chat;  
                  
                strcpy(userInfo.name,Name);  
                  
                ret = write(sfd, &userInfo,sizeof(userInfo));  
                if(ret == -1)  
                {  
                    perror("write");  
                    return -1;  
                }  
                system("clear");  
                printf("\n\n\n\n\n\t\t\t正在发送...\n");  
                sleep(2);  
                  
                break;  
            }  
            case 'c':                   //文件传输  
            {  
                deal_sendfile(sfd);  
                break;  
            }  
            case 'd':                   //查看在线人数  
            {  
                userInfo.cmd = online_member;  
                  
                ret = write(sfd, &userInfo,sizeof(userInfo));  
                if(ret == -1)  
                {  
                    perror("write");  
                    return -1;  
                }  
                  
                system("clear");  
                printf("\n\n\n\n\n\n\t\t...\n");  
                break;  
            }  
            case 'e':                   //发送表情  
            {  
                deal_send_expr(sfd);  
                break;  
            }  
            case 'f':                   //发送常用语  
            {  
                deal_phrases(sfd);  
                break;  
            }  
            case 'g':                   //点赞  
            {  
                userInfo.cmd = like;  
                system("clear");  
                printf("\n\n\n\n\n\n\t\t您比较欣赏谁呢？`(*∩_∩*)′请告诉我：");  
                scanf("%s", userInfo.toname);  
                SCAN_N();  
                strcpy(userInfo.name, Name);  
                  
                if(strcmp(Name, userInfo.toname) == 0)  
                {  
                    sleep(1);  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t不可以给自己点赞哦`(*∩_∩*)′");  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                  
                ret = write(sfd, &userInfo,sizeof(userInfo));  
                if(ret == -1)  
                {  
                    perror("write");  
                    return -1;  
                }  
                printf("\n\n\t\t请稍等...\n");  
                sleep(2);  
                break;  
            }  
            case 'h':                   //更改个性签名  
            {  
                userInfo.cmd = motto_change;  
                system("clear");  
                printf("\n\n\n\n\n\n\t\t您想要一个什么样的个性签名呢？\n\n\n\t\t\t\t");  
                scanf("%s", userInfo.moto);  
                SCAN_N();  
                  
                strcpy(userInfo.name, Name);  
                  
                ret = write(sfd, &userInfo, sizeof(userInfo));  
                if(ret == -1)  
                {  
                    perror("write");  
                    return -1;  
                }  
                printf("\n\n\t\t请稍等...\n");  
                sleep(2);  
                break;  
            }  
            case 'i':                   //注册会员  
            {  
                if(userBack.vip == 1)  
                {  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t\t您已经是尊贵的黄金会员了！`(*∩_∩*)′\n");  
                    printf("\n\n\n\t\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                }  
                else if(userBack.vip == 0)  
                {  
                    system("clear");  
                    printf("\n\n\n\t您好，请先支付200元，然后就能永久享受vip权限了！`(*∩_∩*)′\n");  
                    printf("\n\n\n\n\n\t确认支付吗？（y/n）");  
                    scanf("%s",x);  
                    SCAN_N();  
                      
                    if(x[0] == 'y')  
                    {  
                        strcpy(userInfo.name,Name);  
                        userInfo.vip = 1;  
                        userInfo.cmd = Vip;  
                          
                        ret = write(sfd, &userInfo, sizeof(userInfo));  
                        if(ret == -1)  
                        {  
                            perror("write");  
                            return -1;  
                        }  
                        printf("\n\n\t\t请稍等...\n");  
                        sleep(2);  
                    }  
                }  
                break;  
            }  
            case 'j':                   //禁言  
            {  
                if(userBack.vip == 0)  
                {  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t您还没有开通会员，请先开通会员！`(*∩_∩*)′\n");  
                    printf("\n\n\n\t\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                }  
                else if(userBack.vip == 1)  
                {  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t您想让谁闭嘴呢？`(*∩_∩*)′请告诉我：");  
                    scanf("%s", userInfo.toname);  
                    SCAN_N();  
                    userInfo.cmd = Shutup;  
                    strcpy(userInfo.name,Name);  
                      
                    if(strcmp(Name, userInfo.toname) == 0)  
                    {  
                        sleep(1);  
                        system("clear");  
                        printf("\n\n\n\n\n\n\t\t不可以给自己禁言哦`(*∩_∩*)′");  
                        printf("\n\n\n\t\t输入ENTER键返回：");  
                        fgets(fan, 20, stdin);  
                        break;  
                    }  
                      
                    ret = write(sfd, &userInfo, sizeof(userInfo));  
                    if(ret == -1)  
                    {  
                        perror("write");  
                        return;  
                    }  
                    printf("\n\n\t\t请稍等...\n");  
                    sleep(2);  
                }  
                break;  
            }  
            case 'k':                   //解禁  
            {  
                if(State == 0)  
                {  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t您没有被禁言！尽情聊天吧`(*∩_∩*)′\n");  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                }  
                else if(State == Shutup)  
                {  
                    if(userBack.vip == 0)  
                    {  
                        system("clear");  
                        printf("\n\n\n\n\n\n\t\t您还没有开通会员，请先开通会员！`(*∩_∩*)′\n");  
                        printf("\n\n\n\t\t输入ENTER键返回：");  
                        fgets(fan, 20, stdin);  
                    }  
                    else if(userBack.vip == 1)  
                    {  
                        system("clear");  
                        printf("\n\n\n\n\n\n\t\t您想现在解禁吗！(y/n)：");  
                        scanf("%s",x);  
                        SCAN_N();  
                          
                        if(x[0] == 'y')  
                        {  
                            State = 0;  
                            system("clear");  
                            printf("\n\n\n\n\n\n\t\t恭喜您成功解禁！尽情去嗨皮啊！`(*∩_∩*)′\n");  
                            printf("\n\n\n\t\t输入ENTER键返回：");  
                            fgets(fan, 20, stdin);  
                        }  
                    }  
                }  
                break;  
            }  
            case 'l':                   //踢人  
            {  
                if(userBack.vip == 0)  
                {  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t您还没有开通会员，请先开通会员！`(*∩_∩*)′\n");  
                    printf("\n\n\n\t\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                }  
                else  
                {  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t您看谁不顺眼呢？`(*∩_∩*)′请告诉我：");  
                    scanf("%s", userInfo.toname);  
                    SCAN_N();  
                      
                    strcpy(userInfo.name, Name);  
                    userInfo.cmd = kick;                      //vip踢人信号  
                      
                    if(strcmp(Name, userInfo.toname) == 0)  
                    {  
                        sleep(1);  
                        system("clear");  
                        printf("\n\n\n\n\n\n\t\t不可以踢自己哦`(*∩_∩*)′");  
                        printf("\n\n\n\t\t输入ENTER键返回：");  
                        fgets(fan, 20, stdin);  
                        break;  
                    }  
                      
                    ret = write(sfd, &userInfo, sizeof(userInfo));  
                    if(ret == -1)  
                    {  
                        perror("write");  
                        return;  
                    }  
                    printf("\n\n\t\t请稍等...\n");  
                    sleep(2);  
                }  
                break;  
            }  
            case 'm':                   //查看聊天记录  
            {  
                system("clear");  
                char n[20];  
                char mcf[60];  
                char ncf[2048];  
                char kl;  
                int fd2;  
                int i = 0;  
                printf("\n\n\n\n\n\n\t\t您想看和谁的聊天记录呢？");  
                scanf("%s",n);  
                SCAN_N();  
                sprintf(mcf, "%s与%s的聊天记录.txt", Name, n);  
                fd2 = open(mcf,O_RDONLY,S_IRUSR | S_IWUSR);  
                if(fd2 == -1)  
                {  
                    system("clear");  
                    printf("\n\n\n\n\n\n\n\t\t\t您与%s还没有聊天记录！快去聊天吧`(*∩_∩*)′\n",n);  
                    printf("\n\n\n\t\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                  
                while(1)  
                {  
                    memset(&kl, 0, sizeof(kl));  
                    ssize_t read_bytes = read(fd2, &kl, sizeof(kl));  
                    if(read_bytes == -1)  
                    {  
                        perror("read");  
                        return -1;  
                    }  
                    if(read_bytes == 0)  
                    {  
                        break;  
                    }  
                    ncf[i] = kl;   
                    i++;  
                }  
                ncf[i] = '\0';  
                  
                printf("\n%s\n", ncf);  
                  
                printf("\n\n\n\t\t输入ENTER键返回：");  
                fgets(fan, 20, stdin);  
                break;  
            }  
            case 'n':                   //退出  
            {  
                userInfo.cmd = exit;  
                strcpy(userInfo.name, Name);  
                  
                ret = write(sfd, &userInfo, sizeof(userInfo));  
                if(ret == -1)  
                {  
                    perror("write");  
                    return -1;  
                }  
                return Exit;  
            }  
            case 10:                    //ENTER键返回刷新界面  
            {  
                break;  
            }  
            default:  
            {  
                system("clear");  
                printf("\n\n\n\n");  
                printf("\n\n\t\t请输入a--n之间的选择！\n");  
                printf("\n\n\n\t\t输入ENTER键返回：");  
                fgets(fan, 20, stdin);  
                break;  
            }  
        }  
          
    }  
      
}  
  
int main(int argc, char** argv)  
{  
    if(argc != 2)  
    {  
        printf("Usage: ./cilent IP\n");  
        return -1;  
    }  
      
    int sfd;  
    char bcf[2];  
    pthread_t ReadId;  
    sfd = tcp_connect(argv[1]);  
      
    Welecome();  
      
    while(1)  
    {  
        show();  
        scanf("%s", bcf);  
          
        switch (bcf[0])  
        {  
            case '1':               //注册  
            {  
                if(show_reg() == -9)  
                {  
                    break;  
                }  
                else  
                {  
                    write(sfd, &userInfo, sizeof(userInfo));  
                    memset(&userInfo,0,sizeof(userInfo));  
                      
                    memset(&userBack,0,sizeof(userBack));  
                    read(sfd, &userBack, sizeof(userBack));  
                      
                    if(userBack.result == reg_success)  
                    {  
                        printf("\n\n\t\t\t\t恭喜您注册成功！\n");  
                        printf("\n\n\n\t\t输入ENTER键返回：");  
                        fgets(fan, 20, stdin);  
                    }  
                    else if(userBack.result == existing_acc)  
                    {  
                        printf("\n\n\t\t\t\t该账户已被注册！请重新注册！\n");  
                        printf("\n\n\n\t\t输入ENTER键返回：");  
                        fgets(fan, 20, stdin);  
                    }  
                    break;  
                }  
            }  
            case '2':               //登录  
            {  
                userInfo.cmd = log;  
                show_log(&userInfo);  
                write(sfd, &userInfo, sizeof(struct send));  
                  
                read(sfd, &userBack,sizeof(userBack));  
                  
                if(userBack.result == log_success)  
                {  
                    strcpy(Name, userBack.from_name);  
                    LIKES = userBack.likes;  
                    printf("\n\n\t\t\t\t恭喜您登陆成功！\n");  
                    sleep(2);  
                      
                    pthread_create(&ReadId, NULL, (void*)Read_from_server, (void*)sfd);  
                    pthread_detach(ReadId);  
                      
                    ret = deal_log(sfd);  
                    if(ret == Exit)  
                    {  
                        break;  
                    }  
                }  
                else if(userBack.result == error)  
                {  
                    printf("\n\n\t\t\t\t账号密码错误！请重新登陆\n");  
                    sleep(2);  
                }  
                else if(userBack.result == logged_acc)  
                {  
                    printf("\n\n\t\t\t\t此账号已被登录！\n");  
                    sleep(2);  
                }  
                  
                break;  
            }  
            case '3':               //忘记密码  
            {  
                char ans[100];  
                userInfo.cmd = forget;  
                system("clear");  
                printf("\n\n\n\n\n\n\t\t请输入您的账号：");  
                scanf("%s", userInfo.account);  
                  
                ret = write(sfd, &userInfo, sizeof(userInfo));  
                if(ret == -1)  
                {  
                    perror("write");  
                    return -1;  
                }  
                  
                ret = read(sfd, &userBack, sizeof(userBack));  
                if(ret == -1)  
                {  
                    perror("read");  
                    return -1;  
                }  
                  
                printf("\n\t\t   问题：%s",userBack.question);  
                printf("\n\n\t\t请输入答案:");  
                scanf("%s",ans);  
                SCAN_N();  
                  
                if(strcmp(ans, userBack.answer) == 0)  
                {  
                    printf("\n\n\t\t您的密码是：%s 请妥善保管您的密码`(*∩_∩*)′\n",userBack.passward);  
                      
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                else  
                {  
                    system("clear");  
                    printf("\n\n\n\n\n\n\t\t抱歉，您的答案不对！\n");  
                    printf("\n\n\n\t\t输入ENTER键返回：");  
                    fgets(fan, 20, stdin);  
                    break;  
                }  
                  
            }  
            case '4':               //退出  
            {  
                Byebye();  
                system("clear");  
                return 0;  
            }  
            default :  
            {  
                system("clear");  
                printf("\n\n\n\n");  
                printf("\n\n\t\t请输入1--3之间的选择！\n");  
                sleep(2);  
                break;  
            }  
        }  
    }  
      
    return 0;  
}  