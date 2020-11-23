#include <stdio.h>
#include <stdlib.h>
typedef struct LinkNode
{
    int coef;  //����ʽϵ����ֵ
    int index; //����ʽָ����ֵ
    struct LinkNode *next;
} LinkNode, *LinkList;
//β�巨��������ʽ�ĵ�����
void CreatList(LinkList *L)
{
    LinkList p, q;
    int c, a;                                  //�������ʽϵ����ָ������ʱֵ
    *L = (LinkNode *)malloc(sizeof(LinkNode)); //Ϊ����ʽ�������ͷ�������ռ�
    p = *L;
    scanf("%d %d", &c, &a); //ѭ��Ϊ����ʽ��ֵ
    while (c != 0)
    {
        q = (LinkNode *)malloc(sizeof(LinkNode));
        q->coef = c;
        q->index = a;
        p->next = q;
        p = q;
        scanf("%d %d", &c, &a);
    }
    p->next = NULL;
}
//��������ٲ���
void ClearList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next; //pָ������ĵ�һ���ڵ�
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;
}
//����ʽ����Ӳ���
void AddList(LinkList ha, LinkList hb, LinkList *hc)
{
    LinkList p, q, s, t; //p�洢ha��ֵq����hb ��ֵsΪhc������½��ڵ㣬tΪhcָ��β�����
    int NumCoef;
    *hc = (LinkNode *)malloc(sizeof(LinkNode));
    t = *hc;
    p = ha->next; //pָ��ha�ĵ�һ��Ԫ��
    q = hb->next; //qָ��hb�ĵ�һ��Ԫ��
    while (p != NULL && q != NULL)
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        if (p->index < q->index) //p��ָ��ֵС��q��ָ��ֵʱ��p���ݴ洢����������
        {
            s->coef = p->coef; //�����������ָ�����������������ָ����ϵ���洢�µĶ���ʽ��
            s->index = p->index;
            t->next = s; //β�巨�����µĽ��s
            t = s;
            p = p->next;
        }
        else if (p->index == q->index) //p��ָ��ֵ����q��ָ��ֵʱ��ϵ�����Ȼ������ݴ洢����������
        {
            NumCoef = p->coef + q->coef;
            if (NumCoef != 0) //�ж�ϵ���ĺ��Ƿ�Ϊ0��Ϊ�����޸�ϵ��ֵ
            {
                s->coef = NumCoef;
                s->index = p->index;
                t->next = s;
                t = s;
                p = p->next;
                q = q->next;
            }
        }
        else //p��ָ��ֵ������q��ָ��ֵʱ��q���ݴ洢����������
        {
            s->coef = q->coef;
            s->index = q->index;
            t->next = s;
            t = s;
            q = q->next;
        }
    }
    if (p != NULL) //�ж�2������ʽ�е�Ԫ���Ǹ����������Ϊ����Ϊ�������β��
        t->next = p;
    else
        t->next = q;
}
void DifferList(LinkList ha, LinkList hb, LinkList *hc)
{
    LinkList p, q, s, t; //p�洢ha��ֵq����hb ��ֵsΪhc������½��ڵ㣬tΪhcָ��β�����
    int NumCoef;
    *hc = (LinkNode *)malloc(sizeof(LinkNode));
    t = *hc;
    p = ha->next; //pָ��ha�ĵ�һ��Ԫ��
    q = hb->next; //qָ��hb�ĵ�һ��Ԫ��
    while (p != NULL && q != NULL)
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        if (p->index < q->index) //p��ָ��ֵС��q��ָ��ֵʱ��p���ݴ洢����������
        {
            s->coef = p->coef; //�����������ָ�����������������ָ����ϵ���洢�µĶ���ʽ��
            s->index = p->index;
            t->next = s; //β�巨�����µĽ��s
            t = s;
            p = p->next;
        }
        else if (p->index == q->index) //p��ָ��ֵ����q��ָ��ֵʱ��ϵ�����Ȼ������ݴ洢����������
        {
            NumCoef = p->coef - q->coef;
            if (NumCoef != 0) //�ж�ϵ���ĺ��Ƿ�Ϊ0��Ϊ�����޸�ϵ��ֵ
            {
                s->coef = NumCoef;
                s->index = p->index;
                t->next = s;
                t = s;
                p = p->next;
                q = q->next;
            }
        }
        else //p��ָ��ֵ������q��ָ��ֵʱ��q���ݴ洢����������
        {
            s->coef = q->coef;
            s->index = q->index;
            t->next = s;
            t = s;
            q = q->next;
        }
    }
    if (p != NULL) //�ж�2������ʽ�е�Ԫ���Ǹ����������Ϊ����Ϊ�������β��
        t->next = p;
    else
        t->next = q;
}
//��ӡ����
void PrintList(LinkList head)
{
    LinkList p;
    int c, a;
    p = head->next;
    while (p->next != NULL)
    {
        c = p->coef;
        a = p->index;
        printf("%dX^%d+", c, a);
        p = p->next;
    }
    c = p->coef;
    a = p->index;
    printf("%dX^%d", c, a);
}
int main()
{
    LinkList La, Lb, Lc;
    printf("�������ʽʱ�Կո���� ϵ���ո�ָ�� ����Ϊ�������룺\n");
    printf("�������һ������ʽ\n");
    CreatList(&La);
    printf("������Ķ���ʽΪ��");
    PrintList(La);
    printf("������ڶ�������ʽ\n");
    CreatList(&Lb);
    printf("������Ķ���ʽΪ��");
    PrintList(Lb);
    printf("\n");
    AddList(La, Lb, &Lc);
    printf("����ʽ��Ӻ�");
    PrintList(Lc);
    printf("\n");
    DifferList(La, Lb, &Lc);
    printf("����ʽ�����");
    PrintList(Lc);
    ClearList(&La);
    ClearList(&Lb);
    ClearList(&Lc);
    getchar();
    return 0;
}

//==================================================//
//            Copyright? 2020 WangXu                //
//            Author:    WangXu                     //
//            Email:     1374299613@qq.com          //
//            Time:      2020-11-03  22:38:20       //
//==================================================//