#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//�˺���ͷ�ļ�Ϊ��ʹ���ַ�������
#include<stdlib.h>//�˺���ͷ�ļ�Ϊ��ʹ�ö�̬�ڴ���亯��
#include<string.h>//�ַ�������ͷ�ļ�
#include<math.h>
#include"structtype.h"//�������Զ���ͷ�ļ�


//�����ʼ����ʱ��ĺ���
void inittemp_routelist(route_type* temproute, route_type* sendroute)
{
	int len = 0;
	route_listdata* p;
	char name[] = "**";
	//initroute(temproute);//��ʼ��·����
	route_listhead* head = (route_listhead*)malloc(sizeof(route_listhead));//���ٱ�ͷ�ڵ㣨ֻ��һ����ͷ��
	head->headcolname1 = "Ŀ������";
	head->headcolname2 = "����";
	head->headcolname3 = "��һ��·��";
	initroutelist(head);
	temproute->routelist = head;

	for (int i = 0; i <strlen(name); i++)
		temproute->selfname[i] = name[i];
	//ͳ�Ʒ��ͷ�����Ľڵ���
	for (p = sendroute->routelist->initdatas; p->nextdata != NULL; p = p->nextdata)
		len++;
	//�÷��ͷ�����ڵ�����ʼ����ʱ·����
	for (int i = 0; i < len; i++)
		insert(temproute);
	printf("��ʱ·������·�ɱ�һ��%d���սڵ㣡\n", len+1);//��Ϊ��ʼ������һ���յ�ͷ�ڵ���Ҫ�ӽ�ȥ���������һ���ڵ��ָ����Ϊ��ʱ�ͽ�����û�мӽ�ȥ
}

//�������ͷ��µ���ʱ·�ɱ�bufferroutelist
void createbuffertable(route_type* sendroute, route_type* temproute)
{
	route_listdata* p1 = sendroute->routelist->initdatas;
	//�������ͷ��µ���ʱ·�ɱ�
	route_listdata* p2 = temproute->routelist->initdatas;
	//�ɷ��ͷ�·�ɱ��ȡ�µ���ʱ·�ɱ�
	while (p1!= NULL)
	{
		p2->distance = p1->distance + 1;//��ԭ���ͷ����ھ��������+1��ֵ����ʱ��ľ����ֶ�
		for (int i = 0; i < Maxsize; i++)
		{
			p2->dnet[i] = p1->dnet[i];
			p2->nextroute[i] = sendroute->selfname[i];//����ʱ���е���һ��·��ȫ����Ϊ���ͷ�·��������
		}
		p1 = p1->nextdata;//��ת����һ���ڵ�
		p2 = p2->nextdata;
	}
}