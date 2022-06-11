#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

struct danci
{
    char s[20];                                   //����
    int colum;                                    //�����к�
    int n;                                        //��n������
    struct danci* next;
};

void savetxt();                                //�������뱣�浽�ļ�
struct danci* read(struct danci* head);        //����һ����������
void chaxun1(struct danci* head, char* str);    //�󵥴ʳ��ֵ��ܴ���
void chaxun2(struct danci* head, char* str);    //�󵥴ʵ�һ�γ������ڵ��кż�λ��
int equal(char* s1, char* s2);                  //�ַ���ƥ��

//�ı��ļ����ʵļ��������������
int main()
{
    printf("�������ı�(��#����):");
    savetxt();
    struct danci* p = NULL;
    p = read(p);
    printf("�������ѯ�ĵ���:");
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
        printf("�޷��򿪴��ļ�\n");
        exit(0);
    }
    char ch;
    ch = getchar();
    while (ch != '#')
    {
        fputc(ch, fp); //fputc()������д�ļ�����(��һָ���ַ�д���ļ�����)
        ch = getchar();
    }
    fclose(fp);
}

struct danci* read(struct danci* head)
{
    FILE* fp;
    if ((fp = fopen("1.txt", "r")) == NULL)
    {
        printf("�޷��򿪴��ļ�\n");
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
    while (ch != EOF)                           //���ļ���ȡ�ַ�
    {

        if (ch == '\n')   //��������.���򡮣�������һ�ַ�Ϊ���з�
        {
            ch = fgetc(fp);
            count = 1;
            col += 1;                            //������һ����������һ
            continue;
        }
        while (ch != ' ' && ch != ',' && ch != '.' && ch != '\n' && ch != EOF)
        {
            p->s[i] = ch;
            i++;
            ch = fgetc(fp);
        }
        p->s[i] = '\0';                          //�ӽ�����־
        i = 0;
        p->colum = col;
        p->n = count;
        if (ch == ' ' || ch == ',' || ch == '.')
        {
            count += 1;                         //������һ
        }
        if (ch == '\n')
        {
            count = 1;
            col += 1;                           //������һ����������һ
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
    }                        //������������
    printf("%s һ������ %d ��\n", str, total);
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
    }                        //������������
    if (flag)
        printf("�õ��ʣ�%s �״γ��ֵ�λ�õ�%d�е�%d������\n", str, head->colum, head->n);
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