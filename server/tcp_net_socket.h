/********************************************************************* 
File Name:               tcp_net_socket.h 
Author:                             date: 
Description:             
Fuction List:            
********************************************************************/  
  
#ifndef TCP_NET_SOCKET_H_  
#define TCP_NET_SOCKET_H_  
  
#include <stdio.h>  
#include <sqlite3.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <string.h>  
#include <strings.h>  
#include <stdlib.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#include <signal.h>  
#include <pthread.h>  
#include <semaphore.h>  
#include <termios.h>  
#include <time.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
  
#define SERV_PORT       9000  
  
/*********************注册登录**********************/  
#define reg             1         //注册  
#define log             2         //登录  
#define forget          3         //忘记密码  
#define exit            4         //退出  
#define existing_acc    5         //账号已存在  
#define logged_acc      6         //账号已登录  
#define error           7         //账号或密码错误  
#define log_success     8         //登录成功  
#define reg_success     9         //注册成功  
#define Exit            10        //退出  
/**************************************************/  
  
/******************聊天室功能**********************/  
#define private_chat    11        //私聊  
#define group_chat      12         //群聊  
#define group_result    13        //群聊接受  
#define file_transfer   14        //文件传输  
#define online_member   15        //查看在线人数  
#define expression      16        //表情  
#define phrases         17        //常用语  
#define motto           18        //个性签名  
#define motto_change    19        //更改个性签名  
#define like            20        //点赞  
#define Vip             21        //开会员  
#define Shutup          22        //禁言  
#define lifted          23        //解禁  
#define kick            24        //踢人  
/**************************************************/  
  
  
/****************服务器返回结果*******************/  
#define vip_success     25        //开会员成功  
#define Shutup_success  26        //禁言成功  
#define Send_success    27         //发送信息成功  
#define Send_error      28         //发送信息失败  
#define kick_fail       29        //踢人失败  
#define kick_success    30        //踢人成功  
#define like_success    31        //点赞成功  
#define change_success  32        //更改个性签名成功  
/************************************************/  
  
extern int tcp_init();  
extern int tcp_accept(int sfd);  
extern int tcp_connet();  
extern void signalhandler(void);  
extern int mygetch();  
extern int gettime();  
extern char* nowtime();  
  
#endif  