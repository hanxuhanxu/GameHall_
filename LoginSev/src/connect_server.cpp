#include "connect_server.h"


connect_server::connect_server()
{
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(4000);
	serverAddr.sin_addr.s_addr = inet_addr("192.168.43.84");
	//创建监听socket

}


connect_server::~connect_server()
{
}
void connect_server::addfd(int epollfd, int fd, bool enable_et)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	if (enable_et)
		ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
	setnonblocking(fd);
	printf("fd added to epoll!\n\n");
}//添加事件
int connect_server::setnonblocking(int sockfd)
//设置非阻塞
{
	fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK);
	return 0;
}
void connect_server::Bind()
{
	if (bind(listener, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("bind error");
		exit(-1);
	}
	//大厅socket
	if (bind(DTlisten, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{

		perror("bind DTlisten error");
		exit(-1);
	}
	
	int recv = listen(DTlisten, 128);
	if (recv<0)
	{
		perror("listen error");
		exit(-1);
	}
	printf("listen is created\n");

}
void connect_server::Listen()
{
	listener = socket(PF_INET, SOCK_DGRAM, 0);
	if (listener < 0) { perror("listener"); exit(-1); }
	printf("listen socket created \n");

	DTlisten = socket(PF_INET, SOCK_STREAM, 0);
	if (listener < 0) { perror("DTlistener"); exit(-1); }
	printf("DTlisten socket created \n");
}
void connect_server::accept_connect(int epollfd, int fd)//用户连上之后要做的事
{
	//我自己用于发送的socket
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (0 > sockfd)
	{
		perror("socket");

	}
	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5577);
	addr.sin_addr.s_addr = inet_addr("192.168.2.177");

	//接受对方信息的socket

	struct sockaddr_in client_addr;
	socklen_t addr_size = sizeof(client_addr);
	char buf[_DEF_SIZE];
	int ret = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &addr_size);
	//check(ret > 0, "recvfrom error");

    printf("client connection from: %s : % d(IP : port), clientfd = %d \n",
                            inet_ntoa(client_addr.sin_addr),
                            ntohs(client_addr.sin_port),
                            fd);

  PackdefType *pType = (PackdefType*)buf;
	if (*pType == _DEF_PROTOCOL_REGISTER_RQ)//注册
	{
		STRU_ONLINE* str =(STRU_ONLINE*) buf;
		int id;

		id=sqlAdd(str->m_username, str->m_password);//表中注册获得ip
		STRU_REGISTER_RS rs;//回复包
		rs.IfSuccess = 1;
		rs.m_nType = _DEF_PROTOCOL_REGISTER_RS;
		rs.m_userId = id;
		int sen;
		sen=sendto(sockfd, (char*)&rs, sizeof(rs), 0, (const sockaddr*)&client_addr, sizeof(client_addr));//给对方回去他的ip
		if(sen>0)
		{
		printf("send suc\n");	}
	}
	else if (*pType == _DEF_PROTOCOL_ONLINE_RQ)//登录
	{
		STRU_LOINRQ *rq = (STRU_LOINRQ*)buf;
		
		STRU_ONLINERS onliners;
		if (sqlfind(rq->m_userId,rq->m_password))
		{
			onliners.IfSuccess = true;
			onliners.m_nType = _DEF_PROTOCOL_ONLINE_RS;//登录回复
			DTinfor dt;
			char ip[16]="192.168.2.13";
            int port=4000;
			memcpy(&dt.IP,&ip,sizeof(ip));
			dt.port=port;
			//memcpy(&dt.port,port,sizeof(port));
		/* 	dt.IP;
			dt.PORT;
			dt = chooseDT();//服务器给他选一个大厅
			*/
			memcpy(&onliners.m_HallIp, dt.IP, sizeof(dt.IP));
		onliners.m_HallPort=dt.port;
			memcpy(&onliners.m_username, rq->m_username, sizeof(rq->m_username));
			
			onliners.m_userId = rq->m_userId;

			
			//给对方回去信息，包括选择大厅后的ip port；
			
		}
		else
			onliners.IfSuccess = false;
		int s=sendto(sockfd, (char*)&onliners, sizeof(onliners), 0, (const sockaddr*)&client_addr, sizeof(client_addr));
	if(s<0)
	{
		
	perror("send error\n");
	}
	}


	//check(ret == 0, "getnameinfo");
	//收到客户端的sockaddr 解开他的信息。这个信息是对方的ip 端口号等等。
	//判断是注册还是登录 
	
	//如果是注册的话 直接表里添加 返回一个id发回去（需要一个表添加函数 返回id）
	//如果是登录  查找id（需要一个查找id函数，返回bool值），有返回登录成功。返回大厅的ip port。

	//
}
void connect_server::Run()
{
	int epfd = epoll_create(EPOLL_SIZE);
	if (epfd < 0) { perror("epfd error"); exit(-1); }
	printf("epoll created, epollfd = %d\n", epfd);
	static struct epoll_event events[EPOLL_SIZE];
	//往内核事件表里添加事件
	addfd(epfd, listener, true);
	addfd(epfd, DTlisten, true);
	//主循环
	/*pthread_t id;
	// 创建心跳检测线程
	//int ret = pthread_create(&id, NULL, heart_handler, (void*)this);
	if (ret != 0)
	{
		perror("Can not create heart-beat checking thread.\n");
	}
	*/
	while (1)
	{
		//epoll_events_count表示就绪事件的数目
		int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
		if (epoll_events_count < 0) {
			perror("epoll failure");
			break;
		}

		printf("epoll_events_count = %d\n", epoll_events_count);
		//处理这epoll_events_count个就绪事件
		for (int i = 0; i < epoll_events_count; ++i)
		{
			int sockfd = events[i].data.fd;
			//新用户连接
			if (sockfd == listener)
			{
				accept_connect(epfd, listener);
			}
		   	else if (sockfd == DTlisten)//大厅连接
			{
				struct sockaddr_in client_address;
				socklen_t client_addrLength = sizeof(struct sockaddr_in);
				int clientfd = accept(listener, (struct sockaddr*)&client_address, &client_addrLength);
				//如果是新用户连接事件的发生 就建立连接，然后再把这个事件加入epfd监听后续事件
				//和大厅链接成功
				printf("client connection from: %s : % d(IP : port), clientfd = %d \n",
					inet_ntoa(client_address.sin_addr),
					ntohs(client_address.sin_port),
					clientfd);
				addfd(epfd, clientfd, true);

				//建立连接 添加事件
//加到链表里
              char *dtIp=(char *)malloc(sizeof(char)*16);
			  dtIp=inet_ntoa(client_address.sin_addr);
            DTsize dt;
			dt.client=clientfd;
			dt.num=0;
			memcpy(&dt.dtinfor.IP,dtIp,sizeof(dtIp));
			//dt.dtinfor.port=ntohs(client_address.sin_port);
            dt.dtinfor.port= ntohs(client_address.sin_port);
			DTlist.push_back(dt);
			printf("add success\n");

			}
			//处理用户发来的消息，并广播，使其他用户收到信息
			else // (events[i].events && EPOLLIN)
			{
				char buf[4096];
				bzero(&buf,sizeof(buf));
			 int rec=recv(sockfd,buf,sizeof(buf),0);
			if(rec<0)
			{
			perror("recv fail\n");
			}
			STRU_HALL_INFO *hall=(STRU_HALL_INFO *)buf;
			//更新大厅人数 一个client 对应一个大厅
			 list<DTsize> ::iterator it;
			for(it=DTlist.begin();it!=DTlist.end();++it)
			{
				if((*it).client==sockfd)
				 {
					(*it).num=hall->m_ManNum;
					break;
					}
				}
			}
		}
	}
}
bool connect_server::sqlfind(int id,char *password)
{
//	int id;
int k;
 char *intstr;
 sprintf(intstr,"%d",id);
 string st=string(intstr);
    string sql = "SELECT password FROM Infor WHERE id = " + st + ";";
	mysql_query(&mysql, sql.c_str());

	MYSQL_RES * result = mysql_store_result(&mysql);
	
    int r = mysql_num_rows(result);
	 MYSQL_ROW row ;
	 row= mysql_fetch_row(result);
	if(r>0)
	        {for (int i = 0; i < mysql_num_fields(result); i++)
	         {
		            cout << row[i];//这里可能需要强转
		             string ps=row[i];
		           const char *p;
					p= ps.c_str();
				//	int k;
					k=strcmp(p,password);//密码正确 k=0
					// id=atoi(sid.c_str());
		             //id=row[i];
		         }
	        // cout << endl;
		    //     row = mysql_fetch_row(result);
		    
}
		if (r == 0||k!=0)//没找到或者密码不对
		return 0;
	else
		return 1;
}
int connect_server::sqlAdd(char *name, char *password)
{
	int id;
    string sname=string(name);
    string spassword=string(password);
cout<<sname;
cout<<spassword;
   //name和password可能也需要转成string
    string sql = "INSERT INTO player(name,password,id)  values('" + sname + "','" + spassword + "',NULL);";
	//string sql = "INSERT INTO Infor (name,sex,age,tel,addr) values('小红','女',18,'13333333333',          '陕西省西安市雁塔区');";
	int k;
	k=mysql_query(&mysql, sql.c_str());
printf("%d\n",k);
    //string sql2 = "select id from player where password='" + spassword + "'";
	string sql2="select @@IDENTITY";
	mysql_query(&mysql, sql2.c_str());
	//执行mysql语句
	MYSQL_ROW row;//=mysql_fetch_row(result);
	MYSQL_RES * result = mysql_store_result(&mysql);
	//获取结果
	row = mysql_fetch_row(result);
	//按行获取下一个
	while (row !=NULL)
	{
		for (int i = 0; i < mysql_num_fields(result); i++)
		{
		cout<<"id" << row[i]<<endl;//这里可能需要强转
            string sid=row[i];//先用string接
            id=atoi(sid.c_str());//转int类型
            //id=row[i];
		}
		cout << endl;
		row = mysql_fetch_row(result);
	}

return id;

}
void  connect_server::connect_mysql()
{
	mysql_init(&mysql);
	/*连接数据库*/
    if(mysql_real_connect(&mysql,"localhost","root","hanxu","mynewdatabase",0,NULL,CLIENT_FOUND_ROWS))
      {
      printf("success\n");
      //mysql_close(&conn);
     }


}
void connect_server::sendDTip()
{
}
DTinfor  connect_server::chooseDT()
{

list<DTsize>::iterator it=DTlist.begin();
int num1=(*it).num;
DTinfor dt;
DTinfor dt2;
if(num1*2< DT_MAX_NUM)
{//如果小于一半 选dt1
dt=(*it).dtinfor;
return dt;}
else
dt2=(*it).dtinfor;

it++;
int num2=(*it).num;

if(num2*2< DT_MAX_NUM)
{//如果第一个>一半 第二个小于 选第二个
dt=(*it).dtinfor;
return dt;
}
if(num1*2> DT_MAX_NUM&&num2*2> DT_MAX_NUM)
{//都大于 选小的那个
	if(num1<num2)
		return dt2;
	else
		dt=(*it).dtinfor;
		return dt;
	
	}
	}

//这一块逻辑是 遍历链表 通过人数 找到最符合条件的大厅 给他发过去;

int main()
{
	connect_server server;
	server.Listen();
	server.Bind();
	server.connect_mysql();
	server.Run();

}
