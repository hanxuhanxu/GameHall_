#include"../include/TCPNet.h"


void CreateUDPSocket()
{
	int rec,len;
	int err;

	UDPSocket=socket(AF_INET,SOCK_DGRAM,0);
	if(UDPSocket<0)
	{
       	   perror("udp sockfd error\n");
	}
	else
	{
 		printf("udp socket create success\n");
	}
	bzero(&server_udp,sizeof(server_udp));

	server_udp.sin_family=AF_INET;
	server_udp.sin_port=htons(8003);
	server_udp.sin_addr.s_addr=inet_addr("10.51.166.165");

	len=sizeof(server_udp);
	if(bind(UDPSocket,(struct sockaddr*)&server_udp,len)<0)
	{
		perror("bind error\n");
	}
	else
	{
		printf("bind udp socket success\n");
	}
 	pthread_t thread_id;

	if((pthread_create(&thread_id, NULL,udp_recv_thread,(void *)UDPSocket))>0)
	{
	    printf("create udp_recv_thread error:%s\n",strerror(err));
		perror("recv thread error\n");
	}
	else
	{
		printf("recv thread create success\n");
	}
	pthread_detach(thread_id);



       //初始化tcp

    	TCPSocket=socket(AF_INET,SOCK_STREAM,0);
	if(TCPSocket<0)
	{
       		perror("tcp sockfd error\n");
	}

	bzero(&server_tcp,sizeof(server_tcp));

	server_tcp.sin_family=AF_INET;
	server_tcp.sin_port=htons(1234);
	server_tcp.sin_addr.s_addr=inet_addr("10.51.166.165");

	len=sizeof(server_tcp);
	if(bind(TCPSocket,(struct sockaddr*)&server_tcp,len)<0)
	{
		perror("tcpsocket bind error\n");
		return ;
	}

	if(-1==listen(TCPSocket,128))
	{
        perror("listen error\n");
		return ;
	}

	//創建accept線程
	pthread_t accept_thread_id;

	if((pthread_create(&accept_thread_id, NULL, tcp_accept_thread,(void *)TCPSocket))>0)
	{
	    printf("create tcp_accept_thread error:%s\n",strerror(err));
		perror("tcp_accept_thread error\n");
	}
	else
	{
		printf("tcp_accept_thread create success\n");
	}
	pthread_detach(accept_thread_id);

   // close(sockfd);
while(1);

}



void  * udp_recv_thread(void * arg)
{
	int recv_len=0;
	char recv_buf[1024]="";
    	int UDPSocket=(int)arg;
	struct sockaddr_in client_udp;
	socklen_t len=sizeof(client_udp);
    	printf("in recv thread...\n");

    while(1)
	{
		
		recv_len=recvfrom(UDPSocket,recv_buf,BUFFSIZE,0,(struct sockaddr*)&client_udp,&len);
		printf("recv_len %d\n",recv_len);
		if(recv_len>0)
		{
             		printf("recv success\n");
		}
 		else
		{
             		perror("recv failed\n");
		}


		PackdefType *pType = (PackdefType*)recv_buf;
                printf("pType = %d\n",*pType);
		if (*pType == _DEF_PROTOCOL_REGISTER_RQ)//注册
		{
			STRU_ONLINE* str =(STRU_ONLINE*) recv_buf;
			printf("username= %s password=%s \n",str->m_username,str->m_password);
			//int id;

			/*id=sqlAdd(str->m_username, str->m_password);//表中注册获得ip
			STRU_REGISTER_RS rs;//回复包
			rs.IfSuccess = 1;
			rs.m_nType = _DEF_PROTOCOL_REGISTER_RS;
			rs.m_userId = id;
			int sen;
			sen=sendto(sockfd, (char*)&rs, sizeof(rs), 0, (const sockaddr*)&client_addr, sizeof(client_addr));//给对方回去他的ip
			if(sen>0)
			{
			printf("send suc\n");	
			}*/
		}
		else if(*pType == _DEF_PROTOCOL_ONLINE_RQ)//登录
		{
                      STRU_ONLINE* str =(STRU_ONLINE*) recv_buf;
		      
		}
	}
	

    close(UDPSocket);
	return NULL;
}

void * tcp_accept_thread(void * arg)
{

	  
	char buf[1024];	  
	socklen_t len=sizeof(client_tcp);
	int accept_fd = accept(TCPSocket, (struct sockaddr*)&client_tcp, &len); 	  
	if(accept_fd < 0)	  
	{		  
		perror("accept error\n");		  
		return NULL;	  
	}	  
	else	  
	{			  
		printf("connected with ip: %s  and port: %d\n", inet_ntop(AF_INET,&client_tcp.sin_addr, buf, 1024), ntohs(client_tcp.sin_port));			 
 	}

	//創建tcp recv 線程
	pthread_t tcp_recv_id;

	if((pthread_create(&tcp_recv_id, NULL, tcp_recv_thread,(void *)TCPSocket))>0)
	{
		perror("tcp_recv_thread error\n");
	}
	else
	{
		printf("tcp_recv_thread create success\n");
	}
	pthread_detach(tcp_recv_id);

	return NULL;
}

void * tcp_recv_thread(void * arg)
{
 	int recv_len=0;
	char recv_buf[1024]="";
    	int TCPSocket=(int)arg;
	struct sockaddr_in client_tcp;
	int len=sizeof(client_tcp);
    	printf("in tcp recv thread...\n");

    while(1)
	{
		
		recv_len=recv(UDPSocket,recv_buf,BUFFSIZE,0);
		printf("recv_len %d\n",recv_len);
		if(recv_len>0)
		{
             		printf("tcp recv success\n");
				//	exit(-1);
		}
 		else
		{
             		perror("tcp recv failed\n");
		}
	}
	

    close(TCPSocket);
	return NULL;
}

void ConnectMysql()
{
	mysql_init(&mysql);
	/*连接数据库*/
    	if(mysql_real_connect(&mysql,"localhost","root","hanxu","db1",0,NULL,CLIENT_FOUND_ROWS))
      	{
      		printf("success\n");

     	}
}


int main()
{
 	CreateUDPSocket();
	ConnectMysql();
}
