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
  
typedef struct node  
{  
    int  socket;  
    char name[20];  
    struct node* next;  
}UMge;  
typedef struct node* PUMge;  
  
struct send userInfo;  
struct recv userBack;  
sqlite3 * db = NULL;            //基础信息存放数据库  
int i;  
int ret;  
PUMge head;                   //在线用户表  
  
//保存用户  
void save_user()  
{  
      
    char *errmsg = NULL;  
    char auff[200] = {0};   
    char cuff[200] = {0};  
    sprintf(auff, "insert into save_user values('%s','%s','%s','%s',%d,%d)",userInfo.account, userInfo.passward, userInfo.name, userInfo.moto, userInfo.likes, userInfo.vip);  
      
    ret = sqlite3_exec(db, auff, NULL, NULL, &errmsg);  
    if(ret != SQLITE_OK)  
    {  
        printf("insert fail:%d(%s)\n", ret, errmsg);  
        userBack.result = existing_acc;             //账号已存在   
        printf("%s is insert error...\n",userInfo.name);  
        return;  
    }  
    printf("sqlite save_user insert success...\n");  
      
    sprintf(cuff,"insert into question values('%s','%s','%s','%s')", userInfo.account, userInfo.passward, userInfo.question, userInfo.answer);  
    ret = sqlite3_exec(db, cuff, NULL, NULL, &errmsg);  
    if(ret != SQLITE_OK)  
    {  
        printf("insert fail:%d(%s)\n", ret, errmsg);  
        return;  
    }  
      
    userBack.result = reg_success;                 //注册成功  
}  
  
//登录检查表和客户端发来的数据对比  
void deal_log(int cfd)  
{  
    char **resultp = NULL;  
    int nrow;  
    int ncolumn;  
    int ret;  
    int i;  
    char *errmsg = NULL;  
    char cuff[200];  
      
    sprintf(cuff, "select account,passward,name,moto,likes,vip from save_user where account = '%s' and passward = '%s'", userInfo.account, userInfo.passward);  
      
    ret = sqlite3_get_table(db, cuff, &resultp, &nrow, &ncolumn, &errmsg);  
    if (ret != SQLITE_OK)  
    {  
        printf ("log error : %d(%s)!\n", ret, errmsg);  
        return;  
    }     
      
    printf("%s is logging...\n", resultp[8]);  
  
    if(nrow == 1)  
    {  
        PUMge temp = head->next;  
        while(temp != head)  
        {  
            if(strcmp(temp->name, resultp[8]) == 0)  
            {  
                userBack.result = logged_acc;  
                printf("%s logged error because him has logged...\n", userInfo.name);  
                return;  
            }  
            temp = temp->next;  
        }  
          
        userBack.result = log_success;    //登录成功  
        strcpy(userBack.from_name, resultp[8]);  
        strcpy(userBack.moto, resultp[9]);  
          
        userBack.likes = *(resultp[10]) - 48;  
        userBack.vip = *(resultp[11]) - 48;  
          
        printf("%s logged success...\n", resultp[8]);  
          
        PUMge p = (PUMge)malloc(sizeof(UMge)/sizeof(char));  
        if(p == NULL)  
        {  
            perror("malloc");  
            return;  
        }  
        p->socket = cfd;  
        strcpy(p->name, resultp[8]);  
        printf("%s 's socket is %d...\n", p->name, p->socket);  
        p->next = head->next;  
        head->next = p;  
    }  
    else  
    {  
        userBack.result = error;          //账号密码错误  
        printf("%s 's passward is error...\n", resultp[8]);  
    }  
      
    ret = write(cfd, &userBack, sizeof(userBack));  
    if(ret == -1)  
    {  
        perror("write");  
        return;  
    }  
}  
  
//忘记密码  
void deal_forget(int cfd)  
{  
    char auff[100];  
    char **resultp = NULL;  
    int nrow;  
    int ncolumn;  
    int ret;  
    char *errmsg = NULL;  
      
    printf("i am select from question...\n");  
      
    sprintf(auff, "select passward, question, answer from question where account = '%s'", userInfo.account);  
    ret = sqlite3_get_table(db, auff,  &resultp, &nrow, &ncolumn, &errmsg);  
    if(ret != SQLITE_OK)  
    {  
        printf("select error fail:%d(%s)\n", ret, errmsg);  
    }  
      
    strcpy(userBack.passward, resultp[3]);  
    strcpy(userBack.question, resultp[4]);  
    strcpy(userBack.answer, resultp[5]);  
      
    write(cfd, &userBack, sizeof(userBack));  
      
}  
  
//处理私聊请求  
int deal_pchar(int cfd)  
{  
    int flag = 0;  
      
    PUMge temp = head->next;   
    while(temp != head)  
    {  
        if(strcmp(temp->name, userInfo.toname) == 0 && temp->socket != cfd)  
        {  
            flag = 1;  
            strcpy(userBack.msg, userInfo.msg);  
            strcpy(userBack.from_name, userInfo.name);  
            userBack.result = private_chat;  
            printf("%s(%d) send %s(%d) ...\n", userInfo.name, cfd,  userInfo.toname, temp->socket);  
            write(temp->socket, &userBack, sizeof(userBack));  
              
            break;  
        }  
        temp = temp->next;  
    }  
      
    if(flag)  
    {  
        userBack.result = Send_success;  
        write(cfd,&userBack, sizeof(userBack));  
          
        printf("%s send a message to %s...\n", userInfo.name, userInfo.toname);  
    }  
    else  
    {  
        userBack.result = Send_error;  
        write(cfd,&userBack, sizeof(userBack));  
          
        printf("%s send error...\n", userInfo.name);  
    }  
}  
  
//处理群聊请求  
int deal_groupchat(int cfd)  
{  
    int flag = 0;  
      
    PUMge temp = head->next;  
    while(temp != head)  
    {  
        if(temp->socket != cfd)  
        {  
            flag = 1;  
            strcpy(userBack.from_name, userInfo.name);  
            strcpy(userBack.msg, userInfo.msg);  
            userBack.result = group_chat;  
              
            write(temp->socket, &userBack, sizeof(userBack));  
        }  
        temp = temp->next;  
    }  
    printf("%s send a msg to everyone...\n",userInfo.name);  
      
    if(flag)  
    {  
        userBack.result = Send_success;  
        write(cfd,&userBack, sizeof(userBack));  
    }  
    else  
    {  
        userBack.result = Send_error;  
        write(cfd,&userBack, sizeof(userBack));  
          
        printf("%s send grep error...\n", userInfo.name);  
    }  
}  
  
//处理查看当前人数  
int deal_member(int cfd)  
{  
    userBack.online_num = 0;  
    int i = 0;  
    PUMge temp = head->next;  
    while(temp != head)  
    {  
        userBack.online_num++;  
        strcpy(userBack.num[i], temp->name);  
        i++;  
        temp = temp->next;  
    }  
    userBack.result = online_member;  
      
    write(cfd,&userBack,sizeof(userBack));  
      
    printf("show online_member success...\n");  
}  
  
//文件传输  
int deal_file_transfer(int cfd)  
{  
    PUMge temp = head->next;  
    int flag = 0;  
    while(temp != head)  
    {  
        if(strcmp(temp->name, userInfo.toname) == 0 && temp->socket != cfd)  
        {  
            flag = 1;  
            userBack.result = file_transfer;  
            strcpy(userBack.from_name, userInfo.name);  
            strcpy(userBack.file, userInfo.file);  
            strcpy(userBack.file_name, userInfo.file_name);  
              
            write(temp->socket, &userBack, sizeof(userBack));  
              
            break;  
        }  
          
        temp = temp->next;  
    }  
      
    if(flag)  
    {  
        userBack.result = Send_success;  
        ret = write(cfd,&userBack, sizeof(userBack));  
        if(ret == -1)  
        {  
            perror("write");  
            return -1;  
        }  
        printf("%s send a file to %s...\n", userInfo.name, userInfo.toname);  
    }  
    else  
    {  
        userBack.result = Send_error;  
        write(cfd,&userBack, sizeof(userBack));  
          
        printf("%s send file error...\n", userInfo.name);  
    }  
}  
  
//发送表情  
int deal_expression(int cfd)  
{  
    PUMge temp = head->next;  
    int flag = 0;  
    while(temp != head)  
    {  
        if(strcmp(temp->name, userInfo.toname) == 0 && temp->socket != cfd)  
        {  
            flag = 1;  
            userBack.result = expression;  
            strcpy(userBack.from_name, userInfo.name);  
            userBack.e_s = userInfo.e_s;  
              
            write(temp->socket, &userBack, sizeof(userBack));  
              
            break;  
        }  
          
        temp = temp->next;  
    }  
      
    if(flag)  
    {  
        userBack.result = Send_success;  
        write(cfd,&userBack, sizeof(userBack));  
          
        printf("%s send a expression to %s...\n", userInfo.name, userInfo.toname);  
    }  
    else  
    {  
        userBack.result = Send_error;  
        write(cfd,&userBack, sizeof(userBack));  
          
        printf("%s send expression error...\n", userInfo.name);  
    }  
}  
  
//发送常用语  
int deal_phrases(int cfd)  
{  
    PUMge temp = head->next;  
    int flag = 0;  
      
    while(temp != head)  
    {  
        if(strcmp(temp->name, userInfo.toname) == 0 && temp->socket != cfd)  
        {  
            flag = 1;  
            userBack.result = phrases;  
            strcpy(userBack.from_name, userInfo.name);  
            userBack.p_s = userInfo.p_s;  
              
            write(temp->socket, &userBack, sizeof(userBack));  
              
            break;  
        }  
          
        temp = temp->next;  
    }  
      
    if(flag)  
    {  
        userBack.result = Send_success;  
        write(cfd,&userBack, sizeof(userBack));  
          
        printf("%s send a phrases to %s...\n", userInfo.name, userInfo.toname);  
    }  
    else  
    {  
        userBack.result = Send_error;  
        write(cfd,&userBack, sizeof(userBack));  
          
        printf("%s send phrases error...\n", userInfo.name);  
    }  
}  
  
//处理点赞请求  
int deal_like(int cfd)  
{  
    int ret;  
    int i;  
    char *errmsg = NULL;  
    char **resultp = NULL;  
    int nrow;  
    int ncolumn;  
    char cuff[200];  
      
    sprintf(cuff, "select likes from save_user where name = '%s'", userInfo.toname);  
      
    ret = sqlite3_get_table(db, cuff, &resultp, &nrow, &ncolumn, &errmsg);  
    if(ret != SQLITE_OK)  
    {  
        printf("select fail:%d(%s)\n", ret, errmsg);  
        return -1;  
    }  
      
    if(nrow == 1)  
    {  
        sprintf(cuff, "update save_user set likes = %d where name = '%s'",*(resultp[1]) - 47, userInfo.toname);  
        ret = sqlite3_exec(db, cuff, NULL, NULL, &errmsg);  
        if(ret != SQLITE_OK)  
        {  
            printf("update fail:%d(%s)\n", ret, errmsg);  
            return -1;  
        }  
          
        PUMge temp = head->next;  
          
        while(temp != head)  
        {  
            if(strcmp(temp->name, userInfo.toname) == 0)  
            {  
                userBack.likes = *(resultp[1]) - 47;  
                userBack.result = like;  
                strcpy(userBack.from_name,userInfo.name);  
                write(temp->socket, &userBack, sizeof(userBack));  
                  
                break;  
            }  
            temp = temp->next;  
        }  
        userBack.result = like_success;  
        write(cfd, &userBack, sizeof(userBack));  
          
    }  
    else  
    {  
        userBack.result = Send_error;  
        write(cfd, &userBack, sizeof(userBack));  
    }  
}  
  
//处理更改个签  
int deal_motochange(int cfd)  
{  
    char xcf[200];  
    char *errmsg = NULL;  
  
    sprintf(xcf, "update save_user set moto = '%s' where name = '%s'",userInfo.moto,userInfo.name);  
      
    ret = sqlite3_exec(db,xcf,NULL,NULL,&errmsg);  
    if(ret != SQLITE_OK)  
    {  
        printf("update fail:%d(%s)\n", ret, errmsg);  
        return -1;  
    }  
      
    strcpy(userBack.moto, userInfo.moto);  
    userBack.result = change_success;  
    write(cfd, &userBack,sizeof(userBack));  
    printf("%s change the moto...\n", userInfo.name);  
      
    return 0;  
}  
  
//处理注册会员  
int deal_vip(int cfd)  
{  
    char guff[200];  
    char *errmsg = NULL;  
    sprintf(guff, "update save_user set vip = %d where name = '%s';", userInfo.vip, userInfo.name);  
      
    ret = sqlite3_exec(db,guff,NULL,NULL,&errmsg);  
    if(ret != SQLITE_OK)  
    {  
        printf("update fail:%d(%s)\n", ret, errmsg);  
        return -1;  
    }  
    userBack.vip = 1;  
    userBack.result = vip_success;  
      
    write(cfd, &userBack,sizeof(userBack));  
      
    printf("%s become vip...\n", userInfo.name);  
      
    return 0;  
}  
  
//处理禁言  
int deal_Shutup(int cfd)  
{  
    PUMge temp = head->next;  
    int flag = 0;  
    while(temp != head)  
    {  
        if(strcmp(temp->name, userInfo.toname) == 0)  
        {  
            flag = 1;  
            userBack.result = Shutup;  
            strcpy(userBack.from_name, userInfo.name);  
            write(temp->socket, &userBack, sizeof(userBack));  
              
        }  
          
        temp = temp->next;  
    }  
      
    if(flag)  
    {  
        userBack.result = Shutup_success;  
        write(cfd, &userBack, sizeof(userBack));  
          
    }  
    else  
    {  
        userBack.result = Send_error;  
        write(cfd, &userBack, sizeof(userBack));  
          
    }  
}  
  
//处理踢人  
int deal_kick(int cfd)  
{  
    PUMge temp = head->next;  
    int flag = 0;  
    while(temp != head)  
    {  
        if(strcmp(temp->name, userInfo.toname) == 0)  
        {  
            flag = 1;  
            userBack.result = kick;  
            strcpy(userBack.from_name, userInfo.name);  
            write(temp->socket, &userBack, sizeof(userBack));  
              
            break;  
        }  
          
        temp = temp->next;  
    }  
      
    if(flag)  
    {  
        userBack.result = kick_success;  
        write(cfd, &userBack, sizeof(userBack));  
          
    }  
    else  
    {  
        userBack.result = Send_error;  
        write(cfd, &userBack, sizeof(userBack));  
          
    }  
}  
  
//处理退出请求  
int deal_exit(int cfd)  
{  
    PUMge temp = head;  
      
    while(temp->next != head)  
    {  
        if(strcmp(temp->next->name, userInfo.name) == 0)  
        {  
            PUMge p = temp->next;  
            temp->next = p->next;  
            free(p);  
            printf("%s logged out...\n", userInfo.name);  
            break;  
        }  
        temp = temp->next;  
    }  
      
    return 0;  
}  
  
void *server_requst(int const cfd)  
{  
    printf("i am dealing...\n");  
    char *errmsg = NULL;  
      
    while(1)  
    {  
        ret = read(cfd, &userInfo, sizeof(userInfo));  
        if(ret == 0)  
        {  
            pthread_exit(NULL);  
        }  
  
        switch (userInfo.cmd)  
        {  
            case (reg) :                    //注册  
            {  
                save_user(db);  
                write(cfd, &userBack,sizeof(userBack));  
                break;  
            }  
            case (log):                     //登陆  
            {  
                deal_log(cfd);  
                break;  
            }  
            case (forget):                  //忘记密码  
            {  
                deal_forget(cfd);  
                break;  
            }  
            case (private_chat):            //私聊  
            {  
                deal_pchar(cfd);  
                break;  
            }  
            case (group_chat):              //群聊      
            {  
                deal_groupchat(cfd);  
                break;  
            }  
            case (file_transfer):           //文件传输  
            {  
                deal_file_transfer(cfd);  
                break;  
            }  
            case (online_member):           //查看在线人数  
            {  
                deal_member(cfd);  
                break;  
            }  
            case (expression):              //发送表情  
            {  
                deal_expression(cfd);  
                break;  
            }  
            case (phrases):                 //发送常用语  
            {  
                deal_phrases(cfd);  
                break;  
            }  
            case (like):                    //点赞  
            {  
                deal_like(cfd);  
                break;  
            }  
            case (motto_change):            //更改个性签名  
            {  
                deal_motochange(cfd);  
                break;  
            }  
            case (Vip):                     //注册会员  
            {  
                deal_vip(cfd);  
                break;  
            }  
            case (Shutup):                  //禁言  
            {  
                deal_Shutup(cfd);  
                break;  
            }  
            case (exit):                    //退出  
            {  
                deal_exit(cfd);  
                break;  
            }  
            case(kick):                     //踢人  
            {  
                deal_kick(cfd);  
                break;  
            }  
        }  
    }  
}  
  
int main()  
{  
    int sfd;  
      
    head = (PUMge) malloc (sizeof(UMge)/sizeof(char));  
    if(head == NULL)  
    {  
        printf("malloc error\n");  
    }  
    head->next = head;  
      
    sfd = tcp_init();  
    // signalhandler();  
      
    char *errmsg = NULL;  
    ret = sqlite3_open("user.db",&db);  
    if(ret != SQLITE_OK)  
    {  
        perror("open user.db error");  
        return -1;  
    }  
    printf("open user.db success...\n");  
      
    ret = sqlite3_exec(db, "create table if not exists save_user(account TEXT, passward TEXT, name TEXT, moto TEXT, likes INTEGER, vip INTEGER, primary key(account))",NULL,NULL,&errmsg);  
    if(ret != SQLITE_OK)  
    {  
        printf("create fail:%d(%s)\n", ret, errmsg);  
        return -1;  
    }  
    printf("create save_user success...\n");  
      
    ret = sqlite3_exec(db, "create table if not exists question(account TEXT, passward TEXT, question TEXT, answer TEXT, primary key(account))", NULL, NULL, &errmsg);  
    if(ret !=SQLITE_OK)  
    {  
        printf("creat fail:%d(%s)\n",ret,errmsg);  
        return -1;  
    }  
      
    pthread_t clientid;  
      
    while(1)  
    {  
        int cfd;  
        cfd = tcp_accept(sfd);  
        if(cfd == -1)  
        {  
            perror("accept");  
            return -1;  
        }  
          
        ret = pthread_create(&clientid, NULL, (void*)server_requst, (void*)cfd);  
        if(ret == -1)  
        {  
            perror("pthread create");  
            return -1;  
        }  
          
        pthread_detach(clientid); // 线程分离  
        pthread_join(clientid, NULL);  
    }  
      
    sqlite3_close(db);  
      
    return 0;  
}  