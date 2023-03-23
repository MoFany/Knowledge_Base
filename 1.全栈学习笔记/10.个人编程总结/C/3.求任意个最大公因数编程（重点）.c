#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MaxSize 500

//求两个数的最大公约数，即找出两个数的最大公因子，1是任何数的因子,即一个数最小的公因数是1
//最大公约数范围：1---它本身

/*静态全局变量*/
static int max_divisor = 0;//全局最大因子
static int max_publicdivisor = 1;//全局最大公因子

void divisor(int (* divisors)[MaxSize], int n){//行级列指针
	for (int row = 0; row < n; row++)
	{
		int number = *(divisors[row]);//每行的第一个元素存储原数

		for (int col = 1; col < number; col++)//最大公约数从1到其自身为止
		{
			if ( number % col == 0)
			{
				//记录某一个数的所以因子
				*(*(divisors+row)+col) = col;
				//printf("%d-->%d ",col, *(*(divisors + row)+col));

				if (max_divisor<col)
				{
					max_divisor = col;//全局变量始终记录最大的因子
				}
			}
		}
		//printf("\n");
	}	
}

/*在二维数组中不同行同一列相等到最后一列为全局最大公因子*/
int maxpublic_divisor(int(*divisors)[MaxSize],int n){//最大公因子的范围：1--max_divisor(最大因子)
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
	int numbers[MaxSize][MaxSize] = {0},n;//输入的数最大不能超过MaxSize，*****************行下标不能动态指定
	printf("一共有几个数：");
	scanf("%d", &n);

	printf("请输入要求最大公约数的数：");
	for (int num = 0; num < n; num++)
	{
		scanf("%d",&numbers[num][0]);//给每行的首元素赋值为要求最大公约数的数
	}

	/*按行调用函数, 核心**************** 行级指针*/
	divisor(numbers,n);
	
	printf("\n输出每个数以及每个数的所以因数：\n");
	for (int row = 0; row < n; row++)
	{
		printf("%3d : ", numbers[row][0]);
		for (int col = 1; col < MaxSize/4; col++)
		{
			if (col > max_divisor)
			{
				break;//若输出因子超过全局最大因子，则终止本行中列元素的输出
			}
			if (numbers[row][col] == 0)
			{
				printf("   *");
				continue;//在1-max_divisor（全局最大因子）这个范围内，若输出的因子中有0；则用*代替0
			}	
			printf("%4d", numbers[row][col]);
		}
		printf("\n\n");
	}

	/*函数调用求最大公因子*/
	printf("全局最大公因子=%d\n", maxpublic_divisor(numbers, n));
}

int main(){
	init_numbers();
	return 0;
}