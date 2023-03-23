#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//此函数头文件为了使用字符串函数
#include<stdlib.h>//此函数头文件为了使用动态内存分配函数
#include<string.h>//字符串函数头文件
#include<math.h>
#include"structtype.h"//蒋明辉自定义头文件


/*负责更新接收方路由表的函数*/
//插入一个新节点并将原节点的数据全部复制
//若下一跳路由不同时，用临时表记录替换收表对应记录
void appendnode(route_type* r, route_listdata* node)//追加，需要怎加新节点
{
	route_listdata* p1=r->routelist->initdatas;
	int j;
	while (p1->nextdata!= NULL)
	{
		p1 = p1->nextdata;//先到最后一个节点
	}
	//然后为新加入的节点各个成员赋值
	for (int i = 0; i < Maxsize; i++)
	{
		p1->dnet[i] = node->dnet[i];
		p1->nextroute[i] = node->nextroute[i];
	}
	p1->distance = node->distance;
	printf("数据节点：%s已经加入！\n",p1->dnet);
	printf("距离：%d已加入！\n",p1->distance);
	printf("下一跳路由：%s已加入！\n",p1->nextroute);//p1->nextroute越界了
		
}

//跟新接收方表的距离（接收方表与临时表中的下一跳相同时，判断距离：若接收方距离>临时距离，则将接收方距离跟新为临时的距离）
void update(route_listdata* acceptnode, route_listdata* tempsendnode)//更新
{
	if (acceptnode->distance > tempsendnode->distance)
	{
		acceptnode->distance = tempsendnode->distance;
		printf("\n接收方此记录中距离更新成功！\n");
	}
	else
		printf("\n新距离大于原距离无法更新！\n");
}
void replace(route_listdata* acceptnode,route_listdata* tempsendnode)//替换，不同增加新节点
{
	for (int i = 0; i < Maxsize; i++)
	{
		acceptnode->dnet[i] = tempsendnode->dnet[i];
		acceptnode->nextroute[i] = tempsendnode->nextroute[i];
	}
	acceptnode->distance = tempsendnode->distance;
	printf("该条记录替换成功！\n");
}

/*算法所在函数*/
//接收方与临时路由器做记录的比较，若零时路由表中某记录不存在与接收方则加入
void temp_compare_accept(route_type* acceptroute,route_type* temproute)
{
	route_listdata* p1;//临时表
	route_listdata* p = acceptroute->routelist->initdatas;
	route_listdata* p2;//接收方表
	//标志量
	int flag=True;
	for (p1 = temproute->routelist->initdatas;p1!= NULL; p1 = p1->nextdata)//p1代表临时路由表
	{
		//循环遍历p2代表接收方路由表
		for (p2 = p; p2!= NULL; p2 = p2->nextdata)
		{
			
			//判断目的网络是否相同，同则进入；不同则改变标志量的值
			if (strcmp(p1->dnet, p2->dnet) == 0)//找见则返回0,否则没找到
			{
				flag = False;
				//判断下一跳是否相同，相同则替换
				if (strcmp(p1->nextroute, p2->nextroute) == 0)
				{
					printf("\n下一跳路由相同了，则替换记录！\n");
					replace(p2,p1);//临时表中的下一跳与接收方相同时，用临时整体替换接收
					break;
				}
				else
				{
					update(p2, p1);//若接收方的路由表与临时路由表对应的下一跳不相同，就比较距离
					break;
				}
			}
			else
				flag = True;//若标志量一直为TRUE时则加入
		}
		//遍历结束之后若某一目的网络不存在于接收方表中，则加入
		if (flag == True)
		{
			printf("\n不存在的目的网络，则加入！\n");
			insert(acceptroute);//目的网络不存在时，尾部插入一个节点，然后将其数据添加进去
			appendnode(acceptroute, p1);//该函数有问题
		}
		//else
			//continue;//注释此语句的作用是为了测试算法执行时调用执行正确的函数
		printf("\n***************************\n");
	}
}


