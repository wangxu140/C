#include <stdio.h>
#include <stdlib.h>
typedef struct LinkNode
{
    int coef;  //多项式系数的值
    int index; //多项式指数的值
    struct LinkNode *next;
} LinkNode, *LinkList;
//尾插法创建多项式的单链表
void CreatList(LinkList *L)
{
    LinkList p, q;
    int c, a;                                  //定义多项式系数，指数的临时值
    *L = (LinkNode *)malloc(sizeof(LinkNode)); //为多项式的链表的头结点申请空间
    p = *L;
    scanf("%d %d", &c, &a); //循环为多项式赋值
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
//链表的销毁操作
void ClearList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next; //p指向链表的第一个节点
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;
}
//多项式的相加操作
void AddList(LinkList ha, LinkList hb, LinkList *hc)
{
    LinkList p, q, s, t; //p存储ha的值q存在hb 的值s为hc链表的新建节点，t为hc指向尾部结点
    int NumCoef;
    *hc = (LinkNode *)malloc(sizeof(LinkNode));
    t = *hc;
    p = ha->next; //p指向ha的第一个元素
    q = hb->next; //q指向hb的第一个元素
    while (p != NULL && q != NULL)
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        if (p->index < q->index) //p的指数值小于q的指数值时把p数据存储在新链表中
        {
            s->coef = p->coef; //如果两项数的指数不相等则将两项数的指数和系数存储新的多项式中
            s->index = p->index;
            t->next = s; //尾插法插入新的结点s
            t = s;
            p = p->next;
        }
        else if (p->index == q->index) //p的指数值等于q的指数值时将系数相加然后把数据存储在新链表中
        {
            NumCoef = p->coef + q->coef;
            if (NumCoef != 0) //判断系数的和是否为0不为零则修改系数值
            {
                s->coef = NumCoef;
                s->index = p->index;
                t->next = s;
                t = s;
                p = p->next;
                q = q->next;
            }
        }
        else //p的指数值大于于q的指数值时把q数据存储在新链表中
        {
            s->coef = q->coef;
            s->index = q->index;
            t->next = s;
            t = s;
            q = q->next;
        }
    }
    if (p != NULL) //判断2个多项式中的元素那个运输结束后为空则为新链表的尾部
        t->next = p;
    else
        t->next = q;
}
void DifferList(LinkList ha, LinkList hb, LinkList *hc)
{
    LinkList p, q, s, t; //p存储ha的值q存在hb 的值s为hc链表的新建节点，t为hc指向尾部结点
    int NumCoef;
    *hc = (LinkNode *)malloc(sizeof(LinkNode));
    t = *hc;
    p = ha->next; //p指向ha的第一个元素
    q = hb->next; //q指向hb的第一个元素
    while (p != NULL && q != NULL)
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        if (p->index < q->index) //p的指数值小于q的指数值时把p数据存储在新链表中
        {
            s->coef = p->coef; //如果两项数的指数不相等则将两项数的指数和系数存储新的多项式中
            s->index = p->index;
            t->next = s; //尾插法插入新的结点s
            t = s;
            p = p->next;
        }
        else if (p->index == q->index) //p的指数值等于q的指数值时将系数相加然后把数据存储在新链表中
        {
            NumCoef = p->coef - q->coef;
            if (NumCoef != 0) //判断系数的和是否为0不为零则修改系数值
            {
                s->coef = NumCoef;
                s->index = p->index;
                t->next = s;
                t = s;
                p = p->next;
                q = q->next;
            }
        }
        else //p的指数值大于于q的指数值时把q数据存储在新链表中
        {
            s->coef = q->coef;
            s->index = q->index;
            t->next = s;
            t = s;
            q = q->next;
        }
    }
    if (p != NULL) //判断2个多项式中的元素那个运输结束后为空则为新链表的尾部
        t->next = p;
    else
        t->next = q;
}
//打印函数
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
    printf("输入多项式时以空格隔开 系数空格指数 并且为升幂输入：\n");
    printf("请输入第一个多项式\n");
    CreatList(&La);
    printf("你输入的多项式为：");
    PrintList(La);
    printf("请输入第二个多项式\n");
    CreatList(&Lb);
    printf("你输入的多项式为：");
    PrintList(Lb);
    printf("\n");
    AddList(La, Lb, &Lc);
    printf("多项式相加后");
    PrintList(Lc);
    printf("\n");
    DifferList(La, Lb, &Lc);
    printf("多项式相减后");
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