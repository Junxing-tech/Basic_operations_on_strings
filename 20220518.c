#define _CRT_SECURE_NO_WARNINGS 1
//35、字符串的基本操作
//程序要求选择合适的存储结构，并实现以下功能： 
//1）.完成串的基本操作，如：串的赋值，比较，连接，插入，删除； 
//2）.实现串的模式匹配，包括：穷举法，BF算法和KMP算法； 
//3）.字符串的应用：字符串的加密与解密；文本文件单词的计数；文本文件单词的检索；
/*
Author:曾俊兴
Topic:字符串的基本操作
Date:2022-5-21
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PYL 10 //字符串的加密与解密的偏移量的范围是0到255

//串的定义
#define MAXSIZE 100
typedef struct
{
	char ch[MAXSIZE]; //存储字符串的数据
	int Len; //字符串的长度

}String;

//串的长度
int StrLength(String* S)
{
	int i = 0;
	while (S->ch[i] != '\0')
	{
		i++;
	}
	S->Len = i;
	return (S->Len);
}

//建立新串
void CreatStr(String* S)
{
	gets(S->ch);
	S->Len = StrLength(S);
}

//串的删除
int StrDelete(String* S, int i, int l)
{
	/*串S中删除从指定位置i开始连续的j个字符*/
	int k;
	if (i + l - 1 > S->Len)
	{
		printf("所要删除的子串越界");
		return 0;
	}
	else
	{
		for (k = i + l - 1; k < S->Len; k++, i++)//把i+l+1后的字符串直接与i-1的字符相连接
		{
			S->ch[i - 1] = S->ch[k];
		}
		S->Len = S->Len - 1;
		S->ch[S->Len] = '\0';
		return 1;
	}
}

//串的插入，插入位置为i
int StrInsert(String* S, String* S1, int i)
{
	int k;
	if (i > S->Len + 1)
	{
		printf("插入位置错误！");
		return 0;
	}
	else if (S->Len + S1 ->Len > MAXSIZE)
	{
		printf("两串长度超过存储空间长度！");
		return 0;
	}
	else
	{
		for (k = S->Len - 1; k >= i - 1; k--)
		{
			S->ch[S1->Len + k] = S->ch[k];
		}
		for (k = 0; k < S1->Len; k++)
		{
			S->ch[i + k - 1] = S1->ch[k];
		}
		S->Len = S->Len + S1->Len;
		S->ch[S->Len] = '\0';
		return 1;
	}
}

//串的比较
int StrCompare(String* S1, String* S2)
{
	int i = 0, flag = 0;
	while (S1->ch[i] != '\0' && S2->ch[i] != '\0')//判断两串是否相等
	{
		if (S1->ch[i] != S2->ch[i])
		{
			flag = 1;
			break;
		}
		else
			i++;
	}
	if (flag == 0 && S1->Len == S2->Len)//相等
		return 0;
	else
		return S1->ch[i] - S2->ch[i];//若不相等，则判断两的大小
}

//串的连接
int StrCat(String* S, String* T)
{
	int i, flag;/*将串T连接在串S的后面*/
	if (S->Len + T->Len <= MAXSIZE)//两串连接后小于MAXSZIE
	{
		for (i = S->Len; i < S->Len + T->Len; i++)
		{
			S->ch[i] = T->ch[i - S->Len];
		}
		S->ch[i] = '\0';
		S->Len += T->Len;
		flag = 1;
	}
	else if (S->Len < MAXSIZE)//两串连接后等于MAXSZIE
	{
		for (i = S->Len; i < MAXSIZE; i++)
			S->ch[i] = T->ch[i - S->Len];
		S->Len = MAXSIZE;
		flag = 0;
	}
	else//两串连接后大于MAXSZIE
		flag = 0;
	return(flag);
}

//串的BF算法实现
//BF算法的思想就是将目标串S的第一个字符与模式串T的第一个字符进行匹配，
//若相等，则继续比较S的第二个字符和 T的第二个字符；
//若不相等，则比较S的第二个字符和T的第一个字符，依次比较下去，直到得出最后的匹配结果。
int BF(String* S, String* S1)
{
	int i = 0, j = 0;
	while (i < strlen(S) && j < strlen(S1)) 
	{
		if (S->ch[i] == S1->ch[j]) 
		{
			i++;
			j++;
		}
		else 
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == strlen(S1)) {
		return i - strlen(S1) + 1;
	}
	return 0;
}

//串的KMP算法
void Next(String* S1, int* next) //lps数组
{
	int index = 0;
	for (int i = 1; i < strlen(S1);)
	{
		if (S1->ch[i] == S1->ch[index])
		{
			next[i] = index + 1;
			index++;
			i++;
		}
		else 
		{
			if (index != 0)
				index = next[index - 1];
			else
			{
				next[i] = 0;
				i++;
			}
		}
	}
}

int KMP(String* S, String* S1) 
{
	int next[10];
	Next(S1, next);
	int i = 0;
	int j = 0;
	while (i < strlen(S) && j < strlen(S1)) 
	{
		if (S->ch[i] == S1->ch[j]) 
		{
			i++;
			j++;
		}
		else 
		{
			if (j != 0)
				j = next[j - 1];
			else
				i++;
		}
	}
	if (j == strlen(S1)) 
	{
		return i - (int)strlen(S1);
	}
	return -1;
}

//字符串的加密与解密
//加密方式:将字符串中的每个字符加上字符在的字符串中的位置和一个偏移量
//加密函数
char* encrypt(String* S)
{
	int i;
	int count = strlen(S);//测量字符串的长度
	for (i = 0; i < count; i++)
	{
		S->ch[i] = S->ch[i] + i + PYL;
	}
	return S;
}
//解密函数
char* dencrypt(String* S)
{
	int i;
	int count = strlen(S);//测量字符串的长度
	for (i = 0; i < count; i++)
	{
		S->ch[i] = S->ch[i] - i - PYL;
	}
	return S;
}
//字符串的加密与解密
void Encrypt_And_Dencrypt(String* S)
{
	int sead;
	printf("请选择字符串的加密或者解密：1，加密 2，解密：");
	scanf("%d", &sead);
	if (sead == 1)
	{
		encrypt(S);
		printf("加密后的字符串: %s\n", S);
	}
	else if (sead == 2)
	{
		dencrypt(S);
		printf("解密后的字符串: %s\n", S);
	}
	else
	{
		printf("输入错误！");
	}

}

//菜单显示子函数
void MenuString()
{
	 printf("\n			串子系统");
	printf("\n=======================================\n");
	printf("\n|		1---建立新串并显示该串及长度	 \n");
	printf("\n|		2---删除子串					 \n");
	printf("\n|		3---插入子串					 \n");
	printf("\n|		4---比较两个串大小				 \n");
	printf("\n|		5---连接两个串					 \n");
	printf("\n|		6---BF算法实现					 \n");
	printf("\n|		7---KMP算法实现					 \n");
	printf("\n|		8---字符串的加密与解密			 \n");
	printf("\n|		0---返回						 \n");
	printf("\n=======================================\n");
	printf("\n请输入菜单号（数字）:");
}

//主函数
int main()
{
	//变量名定义
	int i, len, flag;
	String x, y, z;
	String* S = &x, * S1 = &y, * S2 = &z;
	char ch1, ch2, a;
	ch1 = 'y';
	
	while (ch1 == 'y' || ch1 == 'Y')
	{
		//菜单显示
		MenuString();
		scanf("%c", &ch2);
		getchar();
		//菜单号
		switch (ch2)
		{
		//建立新串并显示该串及长度
		case '1':
				printf("请输入一个字符串:");
				CreatStr(S);
				printf("该串值为:");
				if (S->ch[0] == '\0')
					printf("空串");
				else
				{
					puts(S->ch);
					printf("该串的长度为:%d", S->Len);
				}
				break;
		//删除子串
		case '2':
				printf("请输入要删除的子串的起始位置:");
				scanf("%d", &i);
				printf("请输入要删除的子串的长度:");
				scanf("%d", &len);
				printf("原来串为:");
				puts(S->ch);
				if (flag = StrDelete(S, i, len))
				{
					printf("删除子串成功， 删除后的新串为:");
					puts(S->ch);
				}
				else
					printf("删除子串失败!");
				break;
		//插入子串
		case '3':
				printf("请输入要插入子串在主串中的位置:");
				scanf("%d", &i);
				printf("请输入一个主串:");
				getchar();
				CreatStr(S1);
				printf("原来主串为:");
				puts(S->ch);
				if (flag = StrInsert(S, S1, i))
				{
					printf("插入子串成功！插入后的新的主串为:");
					puts(S->ch);
				}
				else
					printf("插入主串失败");
				break;
		//比较两串大小
		case '4':
				printf("请输入第一个串:");
				CreatStr(S);
				printf("请输入第二串:");
				CreatStr(S1);
				flag = StrCompare(S, S1);
				if (flag > 0)
				{
					printf("第一个串大！");
				}
				else if (flag < 0)
				{
					printf("第二个串大!");
				}
				else
				{
					printf("两个串相等！");
				}
				break;
		//连接两串
		case '5':
				printf("请输入第一个串:");
				CreatStr(S);
				printf("请输入第二个串:");
				CreatStr(S1);
				flag = StrCat(S, S1);
				if (flag)
				{
					printf("连接以后的新串值为:");
					puts(S->ch);
				}
				else
				{
					printf("连接失败!");
				}
				break;
		//BF算法
		case '6':
				printf("BF算法实现\n");
				printf("请输入主串:");
				CreatStr(S);
				printf("请输入子串:");
				CreatStr(S1);
				int bf = BF(S, S1);
				if (bf != 0)
					printf("BF算法成功，该子串在主串首次出现的位置是:%d", bf);
				else
					printf("BF算法失败，该子串与主串不匹配");
				break;
		//KMP算法
		case '7':
				printf("KMP算法实现\n");
				printf("请输入主串:");
				CreatStr(S);
				printf("请输入子串:");
				CreatStr(S1);
				int kmp = KMP(S, S1);
				if (kmp != -1)
					printf("KMP算法成功，该子串在主串首次出现的位置是:%d", kmp);
				else
					printf("KMP算法失败，该子串与主串不匹配");
				break;
		//字符串的加密与解密
		case '8':
			printf("字符串的加密与解密\n");
			printf("请输入需要操作的字符串\n");
			CreatStr(S);
			Encrypt_And_Dencrypt(S);

		case '0':
				ch1 = 'n';
				break;
		default:
				printf("输入有误， 请输入0-8进行选择！");
		}
		if (ch2 != '0')
		{
			printf("\n按回车键继续， 按任意键返回主菜单！\n");
			a = getchar();
			if (a != '\xA')
			{
				getchar();
				ch1 = 'n';
			}
		}
	}
	//结束

	return 0;
}