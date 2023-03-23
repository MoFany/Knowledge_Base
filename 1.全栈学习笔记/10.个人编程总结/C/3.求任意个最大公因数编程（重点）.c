#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MaxSize 500

//�������������Լ�������ҳ���������������ӣ�1���κ���������,��һ������С�Ĺ�������1
//���Լ����Χ��1---������

/*��̬ȫ�ֱ���*/
static int max_divisor = 0;//ȫ���������
static int max_publicdivisor = 1;//ȫ���������

void divisor(int (* divisors)[MaxSize], int n){//�м���ָ��
	for (int row = 0; row < n; row++)
	{
		int number = *(divisors[row]);//ÿ�еĵ�һ��Ԫ�ش洢ԭ��

		for (int col = 1; col < number; col++)//���Լ����1��������Ϊֹ
		{
			if ( number % col == 0)
			{
				//��¼ĳһ��������������
				*(*(divisors+row)+col) = col;
				//printf("%d-->%d ",col, *(*(divisors + row)+col));

				if (max_divisor<col)
				{
					max_divisor = col;//ȫ�ֱ���ʼ�ռ�¼��������
				}
			}
		}
		//printf("\n");
	}	
}

/*�ڶ�ά�����в�ͬ��ͬһ����ȵ����һ��Ϊȫ���������*/
int maxpublic_divisor(int(*divisors)[MaxSize],int n){//������ӵķ�Χ��1--max_divisor(�������)
	int flag,temp;
	
	for (int col = 1; col < max_divisor; col++)
	{
		flag = 1;
		temp = col;
		for (int row = 0; row < n; row++)
		{
			if (temp != divisors[row][col])
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
			max_publicdivisor = temp;
		}
	}
	return max_publicdivisor;
}

void init_numbers()
{
	int numbers[MaxSize][MaxSize] = {0},n;//�����������ܳ���MaxSize��*****************���±겻�ܶ�ָ̬��
	printf("һ���м�������");
	scanf("%d", &n);

	printf("������Ҫ�����Լ��������");
	for (int num = 0; num < n; num++)
	{
		scanf("%d",&numbers[num][0]);//��ÿ�е���Ԫ�ظ�ֵΪҪ�����Լ������
	}

	/*���е��ú���, ����**************** �м�ָ��*/
	divisor(numbers,n);
	
	printf("\n���ÿ�����Լ�ÿ����������������\n");
	for (int row = 0; row < n; row++)
	{
		printf("%3d : ", numbers[row][0]);
		for (int col = 1; col < MaxSize/4; col++)
		{
			if (col > max_divisor)
			{
				break;//��������ӳ���ȫ��������ӣ�����ֹ��������Ԫ�ص����
			}
			if (numbers[row][col] == 0)
			{
				printf("   *");
				continue;//��1-max_divisor��ȫ��������ӣ������Χ�ڣ����������������0������*����0
			}	
			printf("%4d", numbers[row][col]);
		}
		printf("\n\n");
	}

	/*�����������������*/
	printf("ȫ���������=%d\n", maxpublic_divisor(numbers, n));
}

int main(){
	init_numbers();
	return 0;
}