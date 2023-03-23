#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//�˺���ͷ�ļ�Ϊ��ʹ���ַ�������
#include<stdlib.h>//�˺���ͷ�ļ�Ϊ��ʹ�ö�̬�ڴ���亯��
#include<string.h>//�ַ�������ͷ�ļ�
#include<math.h>
#include"structtype.h"//�������Զ���ͷ�ļ�


//·�ɱ���������ͣ�route_listdata
//·�ɱ����ͣ�route_list
//·�������ͣ�route_type


void initroutelist(route_listhead* h);//һ����סҪ���к�������(ȫ������)
void initroute(route_type* r);




/*-----------------------------------------------------------���幦�ܺ���----------------------------------------------------------------------------------------------*/
/*����·������ʼ������--------*/
void initroute(route_type* r)
{
	//void initroutelist(route_listhead * h);//һ����סҪ���к�������
	//·�ɱ��������һ���������γ��й�ϵ�����ӵı�
	//·�ɱ���һ���ڵ㣬������Ϊ��ͷ���ӵ�������
	//�����ͷ�ڵ�
	route_listhead* head = (route_listhead*)malloc(sizeof(route_listhead));//���ٱ�ͷ�ڵ㣨ֻ��һ����ͷ��
	head->headcolname1 = "Ŀ������";
	head->headcolname2 = "����";
	head->headcolname3 = "��һ��·��";
	
	initroutelist(head);//��ʼ��ʱͷ�ڵ�ָֻ��һ���ڵ�
	r->routelist = head;//��·������ָ����ָ��ͷ�ڵ�
	printf("������·�������֣�");
	if (gets(r->selfname) != NULL && r!= NULL)//����·����������
	{
		printf("·������%s��ʼ���ɹ���\n", r->selfname);
		return True;
	}
	else
	{
		printf("·������%s��ʼ��ʧ�ܣ�\n", r->selfname);
		return False;
	}
		

}

/*����·�ɱ���ʼ��·�ɱ�*/
void initroutelist(route_listhead* head)//��ʼ��ͷ�ڵ�ʹ���ʼָ��һ���յ����ݽڵ�
{
	route_listdata* data = (route_listdata*)malloc(sizeof(route_listdata));//·������ʼ����Ĭ���Դ�һ���յ����ݽڵ�
	data->nextdata = NULL;//��һ���ڵ��ָ����Ϊ��
	for (int i = 0; i < Maxsize; i++)
	{
		data->dnet[i] = NULL;
		data->nextroute[i] = NULL;
	}
	data->distance = NULL;
	head->initdatas = data;//��ʼ��ʱͷ�ڵ�ָֻ��һ��Ϊ�յ����ݽڵ�
}

/*��ʼ��������յ�·�ɱ�*/
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
/*ȫ�ֱ�������insert()��������ڵ�ʱ����������*/
static int nodeobject;//������
route_type* cacheroute = NULL;//·������ַ���棬��ͬ��ͬ·�������벻ͬ�ڵ�ʱ���ز�ͬ�ļ���ֵ
void insert(route_type* r)//β���뷨���������������ڵ�
{
	route_listdata* newnode = (route_listdata*)malloc(sizeof(route_listdata));//����Ϊ�������ͷ�ڵ�
	route_listdata* p1 = r->routelist->initdatas;
	newnode->nextdata = NULL;//�½ڵ��ָ������Ϊ��
	while (p1->nextdata!=NULL)
	{
		p1 = p1->nextdata;//�Ƚ�ָ�붨λ��ָ����Ϊ�յĽڵ���
	}
	p1->nextdata = newnode;
	//printf("%p---%p", p1->nextdata,newnode);
	
	//��ͬ·��������ڵ�ʱ������������
	if (cacheroute != r)//�ж��Ƿ�ͬһ̨·����
	{
		nodeobject = 1;
		cacheroute = r;
	}
	else//cacheroute == rͬһ��·����
	{
		++nodeobject;//��̬ȫ�ֱ���
	}
	printf("�����%d���ڵ�ɹ���\n", nodeobject);
}

/*дһ��Ϊ�����ڵ�������ݵĺ���*/
void add_data(route_type* r)
{
	route_listdata* p;
	printf("\n��ֱ�Ŀ�����硢���롢��һ��·�ɸ�ʽ�������ݣ��Կո�ָ���\n");
	for (p = r->routelist->initdatas; p!= NULL; p = p->nextdata)
	{
		printf("\n###################################\n");
		printf("������Ŀ�����磺");
		scanf("%s", p->dnet);

		printf("��������룺");
		scanf("%d", &p->distance);

		printf("��������һ��·�ɣ�");
		scanf("%s",p->nextroute);
	}
}

//дһ�����·�ɱ�ĺ���
void outputtable(route_type* r)
{
	route_listhead* p1 = r->routelist;//�����ͷ
	route_listdata* p2 = r->routelist->initdatas;//���������
	printf("\n��������������·����%s��·�ɱ�������������",r->selfname);
	printf("\n-------------------------------------------\n");
	printf("%s\t%s\t\t%s\n", p1->headcolname1, p1->headcolname2, p1->headcolname3);
	printf("-------------------------------------------\n");
	for (; p2->nextdata != NULL; p2 = p2->nextdata)
	{
		printf("%s\t\t%d \t\t%s\n", p2->dnet, p2->distance, p2->nextroute);
		//�������һ��
	}
	printf("%s\t\t%d \t\t%s\n", p2->dnet, p2->distance, p2->nextroute);
	printf("-------------------------------------------\n");
}

/*����ʼ��һϵ�г���*/
void main_process(route_type *r)
{
	route_listdata *p;
	int l = 0,n;
	initroute(r);//��ʼ��·����,��ʼ�����·�ɱ����Դ�һ���սڵ�
	//��ʼ��������
	initprint(r);//�����ʼ����Ŀձ�
	printf("������������뼸���ڵ�(����һ���սڵ�)��");
	scanf("%d",&n);
	if (n > 1)
	{
		for (int i = 0; i < n - 1; i++)
			insert(r);//����n-1���ڵ㣬��Ϊ��ʼ��ʱ���Դ���һ���ս��
		//ͳ��Ŀǰ�ڵ����
		for (p = r->routelist->initdatas; p->nextdata != NULL; )
		{
			p = p->nextdata;
			l++;//��Ϊ��ʼ������һ���յ�ͷ�ڵ���Ҫ�ӽ�ȥ���������һ���ڵ��ָ����Ϊ��ʱ�ͽ�����û�мӽ�ȥ
		}
		printf("\n#----->%s·������·�ɱ��Ŀǰ��%d���սڵ㣡\n", r->selfname, ++l);
		add_data(r);//�������
		outputtable(r);//���·�ɱ�
	}
	else
		if (n == 1)
		{
			printf("���ò����½ڵ㣬���Դ�һ���սڵ㣡\n");
			add_data(r);//�������
			outputtable(r);//���·�ɱ�
		}
		else
			printf("Ҫ����Ľڵ�������");
	
	//add_data(r);//�������
	//outputtable(r);//���·�ɱ�
}


/*������*/
/*��ʾ��ע����ѭ���պ󷢣�����������Ҫ�յ�·���������֣�������Ҫ���͵�·����������*/
int main()
{
	route_type R1;			//·����1�����շ�
	route_type R2;			//·����2�����ͷ�
	route_type* temproute;	//��ʱ·����ָ��
	int c = 0;
	//�����ʾ���
	printf("ע�⣺��������շ�·�ɣ������뷢�ͷ�·�ɣ�\n\n");

	/*��ʼ��·����*/
	main_process(&R1);		//����·����1
	printf("\n\n");
	getchar();				//��ȡ�س�
	main_process(&R2);		//����·����2
	
	/*1.���ɷ��ͷ�·�ɱ����·�ɱ�*/
	bufferroutelist.temp = &bufferroutelist.buffersedroute;
	temproute = bufferroutelist.temp;
	//���ȵó�ʼ����ʱ·�ɱ�
	printf("\n\n\n");
	inittemp_routelist(temproute,&R2);
	//�Է��ͷ�Ϊ������������ʱ��
	createbuffertable(&R2,temproute);
	//��������õ���ʱ·�ɱ�
	outputtable(temproute);
	printf("\n\n#############��·�ɱ�%s����###############\n",R1.selfname);
	/*2.�����շ��ı�����ʱ�����Աȣ�Ȼ����½��շ��ı�*/
	//���ģ����������㷨ʵ��
	temp_compare_accept(&R1,temproute);
	//������շ�·�������º��·�ɱ�
	outputtable(&R1);
	return 0;
}
