/********************************************************************* 
File Name:               tcp_net_socket.c 
Author:                  胡剑飞        date: 
Description:             
Fuction List:           int tcp_init()                          //用于初始化操作 
                        int tcp_accept(int sfd)                 //用于服务器的接收 
                        int tcp_connect(const char* ip)         //用于客户端的连接 
                        void signalhandler(void)                //用于信号处理，让服务器在按下Ctrl+c或Ctrl+\时不会退出 
********************************************************************/  
  
#include "tcp_net_socket.h"  
  
//用于初始化操作  
int tcp_init()    
{  
    int sfd = socket(AF_INET, SOCK_STREAM, 0);     //创建套接字  
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
      
    ret = listen(sfd,10);           //监听它，并设置允许最大的连接数为10个  
    if(ret == -1)  
    {  
        perror("listen");  
        close(sfd);  
        return -1;  
    }  
      
    return sfd;  
}  
  
//用于服务器的接收  
int tcp_accept(int sfd)  
{  
    struct sockaddr_in clientaddr;  
    memset(&clientaddr, 0, sizeof(struct sockaddr));  
    int addrlen = sizeof(struct sockaddr);  
      
    //sfd接受客户端的连接，并创建新的socket为new_fd，将请求连接的客户端的ip、port保存在结构体clientaddr中  
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
  
//用于客户端的连接  
int tcp_connect(const char* ip)  
{  
    int ret;  
    int sfd = socket(AF_INET, SOCK_STREAM, 0);     //申请新的socket  
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
      
    ret = connect(sfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));       //将sfd连接至指定的服务器网络地址 serveraddr  
    if(ret == -1)  
    {  
        perror("connect");  
        close(sfd);  
        return -1;  
    }  
      
    return sfd;  
}  
  
//用于信号处理，让服务器在按下Ctrl+c或Ctrl+\时不会退出  
void signalhandler(void)  
{  
    sigset_t sigSet;  
    sigemptyset(&sigSet);  
    sigaddset(&sigSet,SIGINT);  
    sigaddset(&sigSet,SIGQUIT);  
    sigprocmask(SIG_BLOCK,&sigSet,NULL);  
}  
  
//用于将密码数字转换为*  
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
  
//获取当前时间   
int gettime()  
{  
    time_t rawtime;  
    struct tm * timeinfo;  
    time ( &rawtime );  
    timeinfo = localtime ( &rawtime );  
    printf ( "%s",asctime (timeinfo) );   
}  
  
//获取当前时间   指针 用于消息记录  
char* nowtime()  
{  
    time_t rawtime;  
    struct tm * timeinfo;  
    time ( &rawtime );  
    timeinfo = localtime ( &rawtime );  
    return asctime (timeinfo);    
}  
  
//清除scanf后的缓存  回车  
void SCAN_N()  
{  
    char ch;  
    while((getchar()) != '\n' && ch != EOF);  
}  
  
int Get_time(void)//六位数组  
{  
    /* int *temp =p; */  
    time_t now ;  
    struct tm *t ;  
    time(&now) ;  
    t = localtime(&now);  
    /* *(temp++) = t->tm_year+1900; 
    *(temp++) = t->tm_mon+1; 
    *(temp++) = t->tm_mday; 
    *(temp++) = t->tm_hour; 
    *(temp++) = t->tm_min; 
    *temp = t->tm_sec; */  
    return (t->tm_mon+1)*1000000+t->tm_mday*10000+t->tm_hour*100+t->tm_min;  
}  
  
void Welecome(void)  
{  
    system("clear");  
    int a =Get_time();  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         W                                     *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         We                                    *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Wel                                   *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welc                                  *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welco                                 *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcom                                *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome t                             *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to                            *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to o                          *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to ou                         *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our                        *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our c                      *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our ch                     *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our cha                    *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chat                   *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chatt                  *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chatti                 *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chattin                *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chatting               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(150000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chatting r             *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(150000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chatting ro            *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(150000);  
      
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chatting roo           *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(150000);  
      
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chatting room          *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(150000);  
      
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Welcome to our chatting room!         *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(150000);  
      
    sleep(2);  
}  
  
  
void Byebye(void)  
{  
    system("clear");  
    int a =Get_time();  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         H                                     *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Ho                                    *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hop                                   *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope                                  *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope t                                *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to s                             *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to se                            *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see                           *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see y                         *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(100000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see yo                        *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see you                       *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see you a                     *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see you ag                    *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see you aga                   *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see you agai                  *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see you again                 *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    system("clear");  
    printf("\n\n\n\n\t\t*************************************************\n");  
    printf("\t\t* 2017-%02d-%02d-%02d-%02d                              *\n",a/1000000,a%1000000/10000,a%10000/100,a%100);  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*         Hope to see you again!                *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                               *\n");  
    printf("\t\t*                                  Author:hjf   *\n");  
    printf("\t\t*************************************************\n");  
    usleep(200000);  
  
    sleep(2);  
}  