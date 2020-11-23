#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//创建一个huffman树的结构体
typedef struct HTNode
{
    int weight;         //权值
    int parent;         //父亲节点的序号
    int lchird, rchird; //左右孩子的序号

} HTNode, *HuffmanTree;
typedef char **HuffmanCode;
HuffmanTree creatTree(int *wet, int n);
//void selectMin(HuffmanTree HT, int k, int &min1, int &min2);
void creatHuffmancode(HuffmanTree HT, HuffmanCode &HC, int n);
int min(HuffmanTree HT, int k);
//创建Huffman树的函数wet为储存权值的数组n为数组的长度
HuffmanTree creatTree(int *wet, int n)
{
    int m = 2 * n - 1;
    int i;
    HuffmanTree HT = (HuffmanTree)malloc(m * sizeof(HTNode));
    if (!HT)
    {
        printf("申请节点失败！");
        exit(-1);
    }
    //遍历叶子节点将其父亲节点和左右孩子的序号初始化
    for (i = 0; i < n; i++)
    {
        HT[i].parent = -1;
        HT[i].lchird = -1;
        HT[i].rchird = -1;
        HT[i].weight = *wet; //将数组wet中的权值赋给叶子节点
        wet++;
    }
    //Huffman书其他节点的初始化
    for (; i < m; i++)
    {
        HT[i].parent = -1;
        HT[i].lchird = -1;
        HT[i].rchird = -1;
        HT[i].weight = 0;
    }
    //定义权值中每次建立二叉树中权值最小的两个节点且parent的序号为-1的序号
    int min1, min2;
    //建立huffman树逐个节点遍历
    for (i = n; i < m; i++) //因为每次建好一个树时i的节点需要更新从除叶子节点以外的节点开始建立Huffman树
    {
        //寻找数组中权值最小的两个函数
        //selectMin(HT, i, min1, min2);
        min1 = min(HT, i);
        min2 = min(HT, i);
        HT[min1].parent = i; //以当前树中的i值作为min1和min2的父亲节点
        HT[min2].parent = i;
        HT[i].lchird = min1; //更新左右孩子的序号
        HT[i].rchird = min2;
        HT[i].weight = HT[min1].weight + HT[min2].weight; //新节点的权值为min1和min2节点权值之和
    }
    return HT; //返回建立好的Huffman树,
}
//寻找最小权值序号的函数
//void selectMin(HuffmanTree HT, int k, int &min1, int &min2)
//{
// min1 = min(HT, k); //调用相应的功能函数
// min2 = min(HT, k);
//}
//min函数返回值为树中最小权值的下标
int min(HuffmanTree HT, int k)
{
    int min;
    int i = 0;
    int minWeight;             //定义最小权值以及其下标的变量
    while (HT[i].parent != -1) //用来判断数组中第一个无父亲结点的结点，防止每次循环用的都是数组中的第一个结点
        i++;
    minWeight = HT[i].weight; //讲第一个parent为1的结点最为最小的权值结点以和后续的结点作比较
    min = i;
    for (; i < k; i++) //逐个结点进行比较
    {
        if (HT[i].weight < minWeight && HT[i].parent == -1)
        {
            minWeight = HT[i].weight;
            min = i;
        }
    }
    HT[min].parent = 1;
    return min; //返回最小权值的序号
}
//通过建立好的Huffman树来编写Huffman编码并且储存到HC的字符数组中
//通过从叶子节点到根节点寻找Huffman编码的方法
void creatHuffmancode(HuffmanTree HT, HuffmanCode &HC, int n)
{
    HC = (HuffmanCode)malloc(n * sizeof(char *)); //为Huffman申请头结点空间相当于数组的头结点
                                                  //判断申请是否成功
    if (!HC)
    {
        printf("为Huffman code申请头结点空间失败");
        exit(1);
    }
    //为储存编码的数组code申请空间
    char *code = (char *)malloc(n * sizeof(char));
    if (!code)
    {
        printf("code申请空间失败！");
        exit(1);
    }
    //数组的最后用字符0为结束字符
    code[n - 1] = '\0';
    for (int i = 0; i < n; i++)
    {
        int current = i;           //当前节点的位置
        int father = HT[i].parent; //父亲结点序号
        int start = n - 1;         //字符储存的开始位置
        while (father != -1)       //当父亲的序号为1时结束循环
        {
            if (HT[father].lchird == current) //当父节点的左孩子为当前节点时为0否则右孩子为1

                code[--start] = '0';
            else
                code[--start] = '1';
            current = father; //从叶子节点向上更新
            father = HT[father].parent;
        }
        HC[i] = (char *)malloc((n - start) * sizeof(char)); //为找到的第i个Huffman编码串申请空间
        if (!HC[i])
        {
            printf("为编码串申请空间失败！");
            exit(1);
        }
        strcpy(HC[i], &code[start]); //将储存编码的code字符数组赋值给HC数组
    }
    for (int i = 0; i < n; ++i)
    {
        printf("%s\n", HC[i]);
    }           //打印Huffman编码
    free(code); //释放保存编码串的临时空间
}
int main()
{
    int w[] = {3, 5, 1, 4, 2}; //用数组w存储各个权值
    int n = 5;                 //表示数组w中的个数

    HuffmanCode HC = NULL;
    HuffmanTree Tree = creatTree(w, n);

    printf("\n从叶子到根结点编码结果为：\n");
    creatHuffmancode(Tree, HC, n);

    system("pause");

    return 0;
}
