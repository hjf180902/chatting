/********************************************************************* 
File Name:               tcp_net_socket.c 
Author:                             date: 
Description:             
Fuction List:           int tcp_init()                          //���ڳ�ʼ������ 
                        int tcp_accept(int sfd)                 //���ڷ������Ľ��� 
                        int tcp_connect(const char* ip)         //���ڿͻ��˵����� 
                        void signalhandler(void)                //�����źŴ����÷������ڰ���Ctrl+c��Ctrl+\ʱ�����˳� 
********************************************************************/  
  
#include "tcp_net_socket.h"  
  
//���ڳ�ʼ������  
int tcp_init()    
{  
    int sfd = socket(AF_INET, SOCK_STREAM, 0);     //�����׽���  
    if(sfd == -1)  
    {  
        perror("socket");  
        return -1;  
    }  
      
    int ret;  
    struct sockaddr_in serveraddr;  
  
    memset(&serveraddr,0,sizeof(struct sockaddr));    
    serveraddr.sin_family = AF_INET;  
    serveraddr.sin_port = htons(SERV_PORT);  
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
      
    ret = bind(sfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));  
    if(ret == -1)  
    {  
        perror("bind");  
        return -1;  
    }  
      
    ret = listen(sfd,10);           //����������������������������Ϊ10��  
    if(ret == -1)  
    {  
        perror("listen");  
        close(sfd);  
        return -1;  
    }  
      
    return sfd;  
}  
  
//���ڷ������Ľ���  
int tcp_accept(int sfd)  
{  
    struct sockaddr_in clientaddr;  
    memset(&clientaddr, 0, sizeof(struct sockaddr));  
    int addrlen = sizeof(struct sockaddr);  
      
    //sfd���ܿͻ��˵����ӣ��������µ�socketΪnew_fd�����������ӵĿͻ��˵�ip��port�����ڽṹ��clientaddr��  
    int new_fd = accept(sfd, (struct sockaddr*)&clientaddr, &addrlen);         
    if(new_fd == -1)  
    {  
        perror("accept");  
        close(sfd);  
        return -1;  
    }  
    printf("%s %d success connet...\n",   
    inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));  
      
    return new_fd;  
}  
  
//���ڿͻ��˵�����  
int tcp_connect(const char* ip)  
{  
    int ret;  
    int sfd = socket(AF_INET, SOCK_STREAM, 0);     //�����µ�socket  
    if(sfd == -1)  
    {  
        perror("socket");  
        return -1;  
    }  
      
    struct sockaddr_in serveraddr;  
      
    memset(&serveraddr, 0,sizeof(struct sockaddr));  
    serveraddr.sin_family = AF_INET;  
    serveraddr.sin_port = htons(SERV_PORT);  
    serveraddr.sin_addr.s_addr = inet_addr(ip);      
      
    ret = connect(sfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));       //��sfd������ָ���ķ����������ַ serveraddr  
    if(ret == -1)  
    {  
        perror("connect");  
        close(sfd);  
        return -1;  
    }  
      
    return sfd;  
}  
  
//�����źŴ����÷������ڰ���Ctrl+c��Ctrl+\ʱ�����˳�  
void signalhandler(void)  
{  
    sigset_t sigSet;  
    sigemptyset(&sigSet);  
    sigaddset(&sigSet,SIGINT);  
    sigaddset(&sigSet,SIGQUIT);  
    sigprocmask(SIG_BLOCK,&sigSet,NULL);  
}  
  
//���ڽ���������ת��Ϊ*  
int mygetch( )  
{  
    struct termios oldt,  
    newt;  
    int ch;  
    tcgetattr( STDIN_FILENO, &oldt );  
    newt = oldt;  
    newt.c_lflag &= ~( ICANON | ECHO );  
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );  
    ch = getchar();  
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );  
    return ch;  
}  
  
//��ȡ��ǰʱ��   
int gettime()  
{  
    time_t rawtime;  
    struct tm * timeinfo;  
    time ( &rawtime );  
    timeinfo = localtime ( &rawtime );  
    printf ( "%s",asctime (timeinfo) );   
}  
  
//��ȡ��ǰʱ��   ָ�� ������Ϣ��¼  
char* nowtime()  
{  
    time_t rawtime;  
    struct tm * timeinfo;  
    time ( &rawtime );  
    timeinfo = localtime ( &rawtime );  
    return asctime (timeinfo);    
}  