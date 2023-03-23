#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//�˺���ͷ�ļ�Ϊ��ʹ���ַ�������
#include<stdlib.h>//�˺���ͷ�ļ�Ϊ��ʹ�ö�̬�ڴ���亯��
#include<string.h>//�ַ�������ͷ�ļ�
#include<math.h>
#include"structtype.h"//�������Զ���ͷ�ļ�


/*������½��շ�·�ɱ�ĺ���*/
//����һ���½ڵ㲢��ԭ�ڵ������ȫ������
//����һ��·�ɲ�ͬʱ������ʱ���¼�滻�ձ��Ӧ��¼
void appendnode(route_type* r, route_listdata* node)//׷�ӣ���Ҫ�����½ڵ�
{
	route_listdata* p1=r->routelist->initdatas;
	int j;
	while (p1->nextdata!= NULL)
	{
		p1 = p1->nextdata;//�ȵ����һ���ڵ�
	}
	//Ȼ��Ϊ�¼���Ľڵ������Ա��ֵ
	for (int i = 0; i < Maxsize; i++)
	{
		p1->dnet[i] = node->dnet[i];
		p1->nextroute[i] = node->nextroute[i];
	}
	p1->distance = node->distance;
	printf("���ݽڵ㣺%s�Ѿ����룡\n",p1->dnet);
	printf("���룺%d�Ѽ��룡\n",p1->distance);
	printf("��һ��·�ɣ�%s�Ѽ��룡\n",p1->nextroute);//p1->nextrouteԽ����
		
}

//���½��շ���ľ��루���շ�������ʱ���е���һ����ͬʱ���жϾ��룺�����շ�����>��ʱ���룬�򽫽��շ��������Ϊ��ʱ�ľ��룩
void update(route_listdata* acceptnode, route_listdata* tempsendnode)//����
{
	if (acceptnode->distance > tempsendnode->distance)
	{
		acceptnode->distance = tempsendnode->distance;
		printf("\n���շ��˼�¼�о�����³ɹ���\n");
	}
	else
		printf("\n�¾������ԭ�����޷����£�\n");
}
void replace(route_listdata* acceptnode,route_listdata* tempsendnode)//�滻����ͬ�����½ڵ�
{
	for (int i = 0; i < Maxsize; i++)
	{
		acceptnode->dnet[i] = tempsendnode->dnet[i];
		acceptnode->nextroute[i] = tempsendnode->nextroute[i];
	}
	acceptnode->distance = tempsendnode->distance;
	printf("������¼�滻�ɹ���\n");
}

/*�㷨���ں���*/
//���շ�����ʱ·��������¼�ıȽϣ�����ʱ·�ɱ���ĳ��¼����������շ������
void temp_compare_accept(route_type* acceptroute,route_type* temproute)
{
	route_listdata* p1;//��ʱ��
	route_listdata* p = acceptroute->routelist->initdatas;
	route_listdata* p2;//���շ���
	//��־��
	int flag=True;
	for (p1 = temproute->routelist->initdatas;p1!= NULL; p1 = p1->nextdata)//p1������ʱ·�ɱ�
	{
		//ѭ������p2������շ�·�ɱ�
		for (p2 = p; p2!= NULL; p2 = p2->nextdata)
		{
			
			//�ж�Ŀ�������Ƿ���ͬ��ͬ����룻��ͬ��ı��־����ֵ
			if (strcmp(p1->dnet, p2->dnet) == 0)//�Ҽ��򷵻�0,����û�ҵ�
			{
				flag = False;
				//�ж���һ���Ƿ���ͬ����ͬ���滻
				if (strcmp(p1->nextroute, p2->nextroute) == 0)
				{
					printf("\n��һ��·����ͬ�ˣ����滻��¼��\n");
					replace(p2,p1);//��ʱ���е���һ������շ���ͬʱ������ʱ�����滻����
					break;
				}
				else
				{
					update(p2, p1);//�����շ���·�ɱ�����ʱ·�ɱ��Ӧ����һ������ͬ���ͱȽϾ���
					break;
				}
			}
			else
				flag = True;//����־��һֱΪTRUEʱ�����
		}
		//��������֮����ĳһĿ�����粻�����ڽ��շ����У������
		if (flag == True)
		{
			printf("\n�����ڵ�Ŀ�����磬����룡\n");
			insert(acceptroute);//Ŀ�����粻����ʱ��β������һ���ڵ㣬Ȼ����������ӽ�ȥ
			appendnode(acceptroute, p1);//�ú���������
		}
		//else
			//continue;//ע�ʹ�����������Ϊ�˲����㷨ִ��ʱ����ִ����ȷ�ĺ���
		printf("\n***************************\n");
	}
}


