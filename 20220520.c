#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

struct danci
{
    char s[20];                                   //单词
    int colum;                                    //所在行号
    int n;                                        //第n个单词
    struct danci* next;
};

void savetxt();                                //键盘输入保存到文件
struct danci* read(struct danci* head);        //建立一个单词链表
void chaxun1(struct danci* head, char* str);    //求单词出现的总次数
void chaxun2(struct danci* head, char* str);    //求单词第一次出现所在的行号及位置
int equal(char* s1, char* s2);                  //字符串匹配

//文本文件单词的计数与检索主函数
int main()
{
    printf("请输入文本(以#结束):");
    savetxt();
    struct danci* p = NULL;
    p = read(p);
    printf("请输入查询的单词:");
    char str[30];
    scanf("%s", str);
    chaxun1(p, str);
    chaxun2(p, str);
    return 0;
}

void savetxt()
{
    FILE* fp;
    if ((fp = fopen("1.txt", "w")) == NULL)
    {
        printf("无法打开此文件\n");
        exit(0);
    }
    char ch;
    ch = getchar();
    while (ch != '#')
    {
        fputc(ch, fp); //fputc()函数：写文件函数(将一指定字符写入文件流中)
        ch = getchar();
    }
    fclose(fp);
}

struct danci* read(struct danci* head)
{
    FILE* fp;
    if ((fp = fopen("1.txt", "r")) == NULL)
    {
        printf("无法打开此文件\n");
        exit(0);
    }
    struct danci* p, * q;
    p = (struct danci*)malloc(sizeof(struct danci));
    head = q = p;
    char ch;
    int col = 1;
    int count = 1;
    int i = 0;
    ch = fgetc(fp);
    while (ch != EOF)                           //从文件读取字符
    {

        if (ch == '\n')   //当遇到‘.’或‘，’的下一字符为换行符
        {
            ch = fgetc(fp);
            count = 1;
            col += 1;                            //行数加一，个数重置一
            continue;
        }
        while (ch != ' ' && ch != ',' && ch != '.' && ch != '\n' && ch != EOF)
        {
            p->s[i] = ch;
            i++;
            ch = fgetc(fp);
        }
        p->s[i] = '\0';                          //加结束标志
        i = 0;
        p->colum = col;
        p->n = count;
        if (ch == ' ' || ch == ',' || ch == '.')
        {
            count += 1;                         //个数加一
        }
        if (ch == '\n')
        {
            count = 1;
            col += 1;                           //行数加一，个数重置一
        }
        if (ch == EOF)
        {
            break;
        }
        q = p;
        p = (struct danci*)malloc(sizeof(struct danci));
        q->next = p;
        ch = fgetc(fp);
    }
    q->next = NULL;
    return head;
}


void chaxun1(struct danci* head, char* str)
{
    int total = 0;
    while (head != NULL)
    {
        if (equal(head->s, str))
            total += 1;
        head = head->next;
    }                        //遍历整个链表
    printf("%s 一共出现 %d 次\n", str, total);
}

void chaxun2(struct danci* head, char* str)
{
    int flag = 0;
    while (head != NULL)
    {
        if (equal(head->s, str))
        {
            flag = 1;
            break;
        }
        head = head->next;
    }                        //遍历整个链表
    if (flag)
        printf("该单词：%s 首次出现的位置第%d行第%d个单词\n", str, head->colum, head->n);
}


int equal(char* s1, char* s2)
{
    int i, l1, l2;
    l1 = strlen(s1);
    l2 = strlen(s2);
    if (l1 != l2)
        return 0;
    for (i = 0; i < l1; i++)
    {
        if (s1[i] != s2[i])
            return 0;
    }
    return 1;
}