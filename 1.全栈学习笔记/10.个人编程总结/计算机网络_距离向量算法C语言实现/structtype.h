#pragma once
/*author:������*/


/*--------------------------------------------------------------------�������·�ɱ�ṹ�壨�м���»��ߵ����Զ������ͣ�-----------------------------------------------------------------*/

/*�궨���ַ�����*/
#define Maxsize 15
#define True 1	//����
#define False 0	//������

/*�ṹ��1����������ݽڵ�*/
typedef struct
{
	char dnet[Maxsize];			//Ŀ������
	int distance;				//����
	char nextroute[Maxsize];	//��һ��·��
	struct list* nextdata;
}route_listdata;
/*�ṹ��2�������ͷ�ڵ�*/
typedef struct list
{
	char* headcolname1;		//Ŀ�������ͷ
	char* headcolname2;		//�����ͷ
	char* headcolname3;		//��һ��·�ɱ�ͷ
	route_listdata* initdatas;	//�����ݣ���ָ�����ָ����
}route_listhead;


/*�ṹ��3����·������·�ɱ�ָ��ָ��·�ɱ�*/
typedef struct list1
{
	char selfname[Maxsize];		//����·����������
	route_listhead* routelist;		//����·�ɱ�������ֵ��
}route_type;//����һ��·����ʵ��


/*�ṹ��4���ɷ��ͷ�·�����Ŀ�����������ʱ·����*/
struct list2
{
	route_type buffersedroute;		//��ʱ·�ɱ�
	route_type* temp;
}bufferroutelist;//�ṹ�����(ȫ�ֱ���)
