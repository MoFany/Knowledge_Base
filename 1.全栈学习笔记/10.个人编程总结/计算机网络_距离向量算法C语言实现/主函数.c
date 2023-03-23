#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//此函数头文件为了使用字符串函数
#include<stdlib.h>//此函数头文件为了使用动态内存分配函数
#include<string.h>//字符串函数头文件
#include<math.h>
#include"structtype.h"//蒋明辉自定义头文件


//路由表表数据类型：route_listdata
//路由表类型：route_list
//路由器类型：route_type


void initroutelist(route_listhead* h);//一定记住要进行函数声明(全局声明)
void initroute(route_type* r);




/*-----------------------------------------------------------定义功能函数----------------------------------------------------------------------------------------------*/
/*定义路由器初始化函数--------*/
void initroute(route_type* r)
{
	//void initroutelist(route_listhead * h);//一定记住要进行函数声明
	//路由表表数据是一个链表，其形成有关系的链接的表
	//路由表是一个节点，让其作为表头链接到表数据
	//定义表头节点
	route_listhead* head = (route_listhead*)malloc(sizeof(route_listhead));//开辟表头节点（只有一个表头）
	head->headcolname1 = "目的网络";
	head->headcolname2 = "距离";
	head->headcolname3 = "下一跳路由";
	
	initroutelist(head);//初始化时头节点只指向一个节点
	r->routelist = head;//让路由器的指针域指向头节点
	printf("请输入路由器名字：");
	if (gets(r->selfname) != NULL && r!= NULL)//输入路由器的名字
	{
		printf("路由器：%s初始化成功！\n", r->selfname);
		return True;
	}
	else
	{
		printf("路由器：%s初始化失败！\n", r->selfname);
		return False;
	}
		

}

/*定义路由表并初始化路由表*/
void initroutelist(route_listhead* head)//初始化头节点使其最开始指向一个空的数据节点
{
	route_listdata* data = (route_listdata*)malloc(sizeof(route_listdata));//路由器初始化后默认自带一个空的数据节点
	data->nextdata = NULL;//第一个节点的指针域为空
	for (int i = 0; i < Maxsize; i++)
	{
		data->dnet[i] = NULL;
		data->nextroute[i] = NULL;
	}
	data->distance = NULL;
	head->initdatas = data;//初始化时头节点只指向一个为空的数据节点
}

/*初始化后输出空的路由表*/
void initprint(route_type* r)
{
	route_listhead* h = r->routelist;
	route_listdata* p = r->routelist->initdatas;
	printf("------------------------------------\n");
	printf("%s\t%s\t%s\n",h->headcolname1,h->headcolname2,h->headcolname3);
	printf("------------------------------------\n");
	printf("%s\t%s\t%s\n",p->dnet,p->distance,p->nextroute);
	printf("------------------------------------\n");

}
/*全局变量控制insert()函数插入节点时计数器问题*/
static int nodeobject;//计数器
route_type* cacheroute = NULL;//路由器地址缓存，不同不同路由器加入不同节点时返回不同的计数值
void insert(route_type* r)//尾插入法，建立单链表插入节点
{
	route_listdata* newnode = (route_listdata*)malloc(sizeof(route_listdata));//假设为单链表的头节点
	route_listdata* p1 = r->routelist->initdatas;
	newnode->nextdata = NULL;//新节点的指针区域为空
	while (p1->nextdata!=NULL)
	{
		p1 = p1->nextdata;//先将指针定位到指针域为空的节点上
	}
	p1->nextdata = newnode;
	//printf("%p---%p", p1->nextdata,newnode);
	
	//不同路由器插入节点时，计数器重置
	if (cacheroute != r)//判断是否同一台路由器
	{
		nodeobject = 1;
		cacheroute = r;
	}
	else//cacheroute == r同一个路由器
	{
		++nodeobject;//静态全局变量
	}
	printf("插入第%d个节点成功！\n", nodeobject);
}

/*写一个为各个节点添加数据的函数*/
void add_data(route_type* r)
{
	route_listdata* p;
	printf("\n请分别按目的网络、距离、下一跳路由格式输入数据，以空格分隔！\n");
	for (p = r->routelist->initdatas; p!= NULL; p = p->nextdata)
	{
		printf("\n###################################\n");
		printf("请输入目的网络：");
		scanf("%s", p->dnet);

		printf("请输入距离：");
		scanf("%d", &p->distance);

		printf("请输入下一跳路由：");
		scanf("%s",p->nextroute);
	}
}

//写一个输出路由表的函数
void outputtable(route_type* r)
{
	route_listhead* p1 = r->routelist;//输出表头
	route_listdata* p2 = r->routelist->initdatas;//输出表内容
	printf("\n·······路由器%s的路由表·······",r->selfname);
	printf("\n-------------------------------------------\n");
	printf("%s\t%s\t\t%s\n", p1->headcolname1, p1->headcolname2, p1->headcolname3);
	printf("-------------------------------------------\n");
	for (; p2->nextdata != NULL; p2 = p2->nextdata)
	{
		printf("%s\t\t%d \t\t%s\n", p2->dnet, p2->distance, p2->nextroute);
		//少输出了一个
	}
	printf("%s\t\t%d \t\t%s\n", p2->dnet, p2->distance, p2->nextroute);
	printf("-------------------------------------------\n");
}

/*主初始化一系列程序*/
void main_process(route_type *r)
{
	route_listdata *p;
	int l = 0,n;
	initroute(r);//初始化路由器,初始化后的路由表中自带一个空节点
	//初始化后的输出
	initprint(r);//输出初始化后的空表
	printf("请问您打算插入几个节点(已有一个空节点)？");
	scanf("%d",&n);
	if (n > 1)
	{
		for (int i = 0; i < n - 1; i++)
			insert(r);//插入n-1个节点，因为初始化时就自带了一个空姐点
		//统计目前节点个数
		for (p = r->routelist->initdatas; p->nextdata != NULL; )
		{
			p = p->nextdata;
			l++;//因为初始化后有一个空的头节点需要加进去，即：最后一个节点的指针域为空时就结束了没有加进去
		}
		printf("\n#----->%s路由器的路由表表目前有%d个空节点！\n", r->selfname, ++l);
		add_data(r);//添加数据
		outputtable(r);//输出路由表
	}
	else
		if (n == 1)
		{
			printf("不用插入新节点，表自带一个空节点！\n");
			add_data(r);//添加数据
			outputtable(r);//输出路由表
		}
		else
			printf("要插入的节点数有误");
	
	//add_data(r);//添加数据
	//outputtable(r);//输出路由表
}


/*主函数*/
/*提示：注意遵循先收后发，即：先输入要收的路由器的名字，再输入要发送的路由器的名字*/
int main()
{
	route_type R1;			//路由器1，接收方
	route_type R2;			//路由器2，发送方
	route_type* temproute;	//临时路由器指针
	int c = 0;
	//输出提示语句
	printf("注意：先输入接收方路由，后输入发送方路由！\n\n");

	/*初始化路由器*/
	main_process(&R1);		//配置路由器1
	printf("\n\n");
	getchar();				//读取回车
	main_process(&R2);		//配置路由器2
	
	/*1.生成发送方路由表的新路由表*/
	bufferroutelist.temp = &bufferroutelist.buffersedroute;
	temproute = bufferroutelist.temp;
	//首先得初始化临时路由表
	printf("\n\n\n");
	inittemp_routelist(temproute,&R2);
	//以发送方为参照来创建临时表
	createbuffertable(&R2,temproute);
	//输出创建好的临时路由表
	outputtable(temproute);
	printf("\n\n#############新路由表：%s内容###############\n",R1.selfname);
	/*2.将接收方的表与临时表做对比，然后更新接收方的表*/
	//核心：距离向量算法实现
	temp_compare_accept(&R1,temproute);
	//输出接收方路由器更新后的路由表
	outputtable(&R1);
	return 0;
}
