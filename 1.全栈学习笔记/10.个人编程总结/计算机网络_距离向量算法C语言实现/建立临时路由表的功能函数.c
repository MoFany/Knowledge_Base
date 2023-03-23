#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//此函数头文件为了使用字符串函数
#include<stdlib.h>//此函数头文件为了使用动态内存分配函数
#include<string.h>//字符串函数头文件
#include<math.h>
#include"structtype.h"//蒋明辉自定义头文件


//定义初始化临时表的函数
void inittemp_routelist(route_type* temproute, route_type* sendroute)
{
	int len = 0;
	route_listdata* p;
	char name[] = "**";
	//initroute(temproute);//初始化路由器
	route_listhead* head = (route_listhead*)malloc(sizeof(route_listhead));//开辟表头节点（只有一个表头）
	head->headcolname1 = "目的网络";
	head->headcolname2 = "距离";
	head->headcolname3 = "下一跳路由";
	initroutelist(head);
	temproute->routelist = head;

	for (int i = 0; i <strlen(name); i++)
		temproute->selfname[i] = name[i];
	//统计发送方链表的节点数
	for (p = sendroute->routelist->initdatas; p->nextdata != NULL; p = p->nextdata)
		len++;
	//用发送方链表节点数初始化临时路由器
	for (int i = 0; i < len; i++)
		insert(temproute);
	printf("临时路由器的路由表一共%d个空节点！\n", len+1);//因为初始化后有一个空的头节点需要加进去，即：最后一个节点的指针域为空时就结束了没有加进去
}

//建立发送方新的临时路由表：bufferroutelist
void createbuffertable(route_type* sendroute, route_type* temproute)
{
	route_listdata* p1 = sendroute->routelist->initdatas;
	//建立发送方新的临时路由表
	route_listdata* p2 = temproute->routelist->initdatas;
	//由发送方路由表获取新的临时路由表
	while (p1!= NULL)
	{
		p2->distance = p1->distance + 1;//将原发送方表在距离基础上+1赋值给临时表的距离字段
		for (int i = 0; i < Maxsize; i++)
		{
			p2->dnet[i] = p1->dnet[i];
			p2->nextroute[i] = sendroute->selfname[i];//将临时表中的下一跳路由全部改为发送方路由器名字
		}
		p1 = p1->nextdata;//跳转到下一个节点
		p2 = p2->nextdata;
	}
}