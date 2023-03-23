#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MaxSize 100
int max_sub_sum(int *a,int left,int right){

	int center, sum, left_sum, right_sum, lefts, rights, s1, s2;
	if (left == right)//若起点与终点索引都指向同一个数
	{
		if (a[left] > 0)//该数的索引在左边时且值大于0，就返回该数
		{
			return a[left];
		}
		else
		{
			return 0;//否则返回0
		}
	}
	else
	{
		center = (left + right) / 2;//二分法，求中值；center 左边为lefts   右边为rights
		
		left_sum = max_sub_sum(a,left,center);//左边求和，左边界不动，右边界向左缩小,初始时letf_sum的值为a[left]或0
		right_sum = max_sub_sum(a, center + 1, right);//右边求和，左边界向右缩小，右边界不动,初始时right_sum的值为a[left]或0

		/// <summary>
		/// 核心是以下两个循环：
		/// 第一个循环：即，s1===>从右往左求各层最大子段和==>即从右往左求lefts，记录最大时刻的lefts（center--->letf）
		/// 第二个循环：即，s2===>从左往右求各层最大子段和==>即从左往右求rights，记录最大时刻的rights（center+1--->right）
		/// 
		/// 最后的返回值：
		/// 当left_sum最大时，最大子段和为： left_sum
		/// 当right_sum最大时，最大子段和为：right_sum
		/// 
		/// 当s1+s2的值大于left_sum与right_sum时，最大子段和为：s1+s2
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="left"></param>
		/// <param name="right"></param>
		/// <returns></returns>

		s1 = 0;//用于保存最大左子段
		lefts = 0;//累加左子段和
		for (int i = center; i >= left; i--)//左边界不动，右边界向左缩小
		{
			lefts = lefts + a[i];//从右center到left累加左子段的每一个元素
			if (lefts > s1)//如果左子段和大于s1，s1为最大左子段和
			{
				s1 = lefts;
			}
		}

		s2 = 0;//用于保存最大右子段
		rights = 0;//累加右子段和
		for (int i = center + 1; i <= right; i++)//左边界向右缩小，右边界不动
		{
			rights = rights + a[i];//从左center+1到right累加右子段的每一个元素
			if (rights > s2)//如果右子段和大于s2,s2为最大右子段
			{
				s2 = rights;
			}
		}
		/// <summary>
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="left"></param>
		/// <param name="right"></param>
		/// <returns></returns>



		if ((s1 + s2) < left_sum && right_sum < left_sum)//当左子段和最大时返回左子段和
		{
			return left_sum;
		}

		if ((s1 + s2) < right_sum)//当右子段和最大时返回右子段和
		{
			return right_sum;
		}

		return s1 + s2;//返回
	}
}

int max_sum3(int *a,int n)
{
	return (max_sub_sum(a, 0, n-1));//left=1----right=n
}

void init()
{
	int a[MaxSize], n;
	printf("数字序列一共包含几个数：");
	scanf("%d",&n);
	printf("请为数组指定%d个值：",n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", a + i);//指定父段
	}
	

	printf("最大子段和：%d\n", max_sum3(a, n));//为保持算法接口的一致，所以通过max_sub3()函数调用max_sub_sum()函数
}

int main(){

	init();
	return 0;
}

