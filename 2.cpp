#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//����һ��huffman���Ľṹ��
typedef struct HTNode
{
    int weight;         //Ȩֵ
    int parent;         //���׽ڵ�����
    int lchird, rchird; //���Һ��ӵ����

} HTNode, *HuffmanTree;
typedef char **HuffmanCode;
HuffmanTree creatTree(int *wet, int n);
//void selectMin(HuffmanTree HT, int k, int &min1, int &min2);
void creatHuffmancode(HuffmanTree HT, HuffmanCode &HC, int n);
int min(HuffmanTree HT, int k);
//����Huffman���ĺ���wetΪ����Ȩֵ������nΪ����ĳ���
HuffmanTree creatTree(int *wet, int n)
{
    int m = 2 * n - 1;
    int i;
    HuffmanTree HT = (HuffmanTree)malloc(m * sizeof(HTNode));
    if (!HT)
    {
        printf("����ڵ�ʧ�ܣ�");
        exit(-1);
    }
    //����Ҷ�ӽڵ㽫�丸�׽ڵ�����Һ��ӵ���ų�ʼ��
    for (i = 0; i < n; i++)
    {
        HT[i].parent = -1;
        HT[i].lchird = -1;
        HT[i].rchird = -1;
        HT[i].weight = *wet; //������wet�е�Ȩֵ����Ҷ�ӽڵ�
        wet++;
    }
    //Huffman�������ڵ�ĳ�ʼ��
    for (; i < m; i++)
    {
        HT[i].parent = -1;
        HT[i].lchird = -1;
        HT[i].rchird = -1;
        HT[i].weight = 0;
    }
    //����Ȩֵ��ÿ�ν�����������Ȩֵ��С�������ڵ���parent�����Ϊ-1�����
    int min1, min2;
    //����huffman������ڵ����
    for (i = n; i < m; i++) //��Ϊÿ�ν���һ����ʱi�Ľڵ���Ҫ���´ӳ�Ҷ�ӽڵ�����Ľڵ㿪ʼ����Huffman��
    {
        //Ѱ��������Ȩֵ��С����������
        //selectMin(HT, i, min1, min2);
        min1 = min(HT, i);
        min2 = min(HT, i);
        HT[min1].parent = i; //�Ե�ǰ���е�iֵ��Ϊmin1��min2�ĸ��׽ڵ�
        HT[min2].parent = i;
        HT[i].lchird = min1; //�������Һ��ӵ����
        HT[i].rchird = min2;
        HT[i].weight = HT[min1].weight + HT[min2].weight; //�½ڵ��ȨֵΪmin1��min2�ڵ�Ȩֵ֮��
    }
    return HT; //���ؽ����õ�Huffman��,
}
//Ѱ����СȨֵ��ŵĺ���
//void selectMin(HuffmanTree HT, int k, int &min1, int &min2)
//{
// min1 = min(HT, k); //������Ӧ�Ĺ��ܺ���
// min2 = min(HT, k);
//}
//min��������ֵΪ������СȨֵ���±�
int min(HuffmanTree HT, int k)
{
    int min;
    int i = 0;
    int minWeight;             //������СȨֵ�Լ����±�ı���
    while (HT[i].parent != -1) //�����ж������е�һ���޸��׽��Ľ�㣬��ֹÿ��ѭ���õĶ��������еĵ�һ�����
        i++;
    minWeight = HT[i].weight; //����һ��parentΪ1�Ľ����Ϊ��С��Ȩֵ����Ժͺ����Ľ�����Ƚ�
    min = i;
    for (; i < k; i++) //��������бȽ�
    {
        if (HT[i].weight < minWeight && HT[i].parent == -1)
        {
            minWeight = HT[i].weight;
            min = i;
        }
    }
    HT[min].parent = 1;
    return min; //������СȨֵ�����
}
//ͨ�������õ�Huffman������дHuffman���벢�Ҵ��浽HC���ַ�������
//ͨ����Ҷ�ӽڵ㵽���ڵ�Ѱ��Huffman����ķ���
void creatHuffmancode(HuffmanTree HT, HuffmanCode &HC, int n)
{
    HC = (HuffmanCode)malloc(n * sizeof(char *)); //ΪHuffman����ͷ���ռ��൱�������ͷ���
                                                  //�ж������Ƿ�ɹ�
    if (!HC)
    {
        printf("ΪHuffman code����ͷ���ռ�ʧ��");
        exit(1);
    }
    //Ϊ������������code����ռ�
    char *code = (char *)malloc(n * sizeof(char));
    if (!code)
    {
        printf("code����ռ�ʧ�ܣ�");
        exit(1);
    }
    //�����������ַ�0Ϊ�����ַ�
    code[n - 1] = '\0';
    for (int i = 0; i < n; i++)
    {
        int current = i;           //��ǰ�ڵ��λ��
        int father = HT[i].parent; //���׽�����
        int start = n - 1;         //�ַ�����Ŀ�ʼλ��
        while (father != -1)       //�����׵����Ϊ1ʱ����ѭ��
        {
            if (HT[father].lchird == current) //�����ڵ������Ϊ��ǰ�ڵ�ʱΪ0�����Һ���Ϊ1

                code[--start] = '0';
            else
                code[--start] = '1';
            current = father; //��Ҷ�ӽڵ����ϸ���
            father = HT[father].parent;
        }
        HC[i] = (char *)malloc((n - start) * sizeof(char)); //Ϊ�ҵ��ĵ�i��Huffman���봮����ռ�
        if (!HC[i])
        {
            printf("Ϊ���봮����ռ�ʧ�ܣ�");
            exit(1);
        }
        strcpy(HC[i], &code[start]); //����������code�ַ����鸳ֵ��HC����
    }
    for (int i = 0; i < n; ++i)
    {
        printf("%s\n", HC[i]);
    }           //��ӡHuffman����
    free(code); //�ͷű�����봮����ʱ�ռ�
}
int main()
{
    int w[] = {3, 5, 1, 4, 2}; //������w�洢����Ȩֵ
    int n = 5;                 //��ʾ����w�еĸ���

    HuffmanCode HC = NULL;
    HuffmanTree Tree = creatTree(w, n);

    printf("\n��Ҷ�ӵ�����������Ϊ��\n");
    creatHuffmancode(Tree, HC, n);

    system("pause");

    return 0;
}
