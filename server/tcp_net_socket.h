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
  
/*********************ע���¼**********************/  
#define reg             1         //ע��  
#define log             2         //��¼  
#define forget          3         //��������  
#define exit            4         //�˳�  
#define existing_acc    5         //�˺��Ѵ���  
#define logged_acc      6         //�˺��ѵ�¼  
#define error           7         //�˺Ż��������  
#define log_success     8         //��¼�ɹ�  
#define reg_success     9         //ע��ɹ�  
#define Exit            10        //�˳�  
/**************************************************/  
  
/******************�����ҹ���**********************/  
#define private_chat    11        //˽��  
#define group_chat      12         //Ⱥ��  
#define group_result    13        //Ⱥ�Ľ���  
#define file_transfer   14        //�ļ�����  
#define online_member   15        //�鿴��������  
#define expression      16        //����  
#define phrases         17        //������  
#define motto           18        //����ǩ��  
#define motto_change    19        //���ĸ���ǩ��  
#define like            20        //����  
#define Vip             21        //����Ա  
#define Shutup          22        //����  
#define lifted          23        //���  
#define kick            24        //����  
/**************************************************/  
  
  
/****************���������ؽ��*******************/  
#define vip_success     25        //����Ա�ɹ�  
#define Shutup_success  26        //���Գɹ�  
#define Send_success    27         //������Ϣ�ɹ�  
#define Send_error      28         //������Ϣʧ��  
#define kick_fail       29        //����ʧ��  
#define kick_success    30        //���˳ɹ�  
#define like_success    31        //���޳ɹ�  
#define change_success  32        //���ĸ���ǩ���ɹ�  
/************************************************/  
  
extern int tcp_init();  
extern int tcp_accept(int sfd);  
extern int tcp_connet();  
extern void signalhandler(void);  
extern int mygetch();  
extern int gettime();  
extern char* nowtime();  
  
#endif  