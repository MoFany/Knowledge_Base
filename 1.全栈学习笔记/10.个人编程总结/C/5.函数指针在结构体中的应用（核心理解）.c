#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
/**
* 结构体类型，包含变量与函数指针，
* C++中表示结构体就是私有成员类
* @author MoFany
*/
typedef struct node {
	//基本类型成员变量，模拟属性
	int a, b;
	//函数指针成员变量，模拟方法
	int (*funpointer)(struct node n);
}nodetype;

/**
* 结构体函数指针成员引用
* @author MoFany
*/
int fp(nodetype node) {
	return node.a + node.b;
}

/**
* 指针函数
* @author MoFany
*/
nodetype new() {
	//创建自定义类型的实例
	nodetype n;
	//函数名就是一个指针
	n.funpointer = fp;
	return n;
}

/**
* @author MoFany
*/
int main() {
	//创建自定义类型的实例
	nodetype node1 = new();

	//实例.成员属性=值
	node1.a = 1;
	node1.b = 1;

	printf("a=%d\nb=%d\na+b=%d\n", node1.a, node1.b, node1.funpointer(node1));
	return 0;
}