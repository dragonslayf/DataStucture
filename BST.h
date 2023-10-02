#pragma once
#include<iostream>
#include<cassert>
#include<string>
#include<vector>
using namespace std;
class BST {
public:
	BST* left{ nullptr };
	BST* right{ nullptr };
	BST* father{ nullptr };
	int data{ 0 };
	BST* positionFind(BST* begin, int x);
	BST* findMin(BST* begin);
	BST* findMax(BST* begin);
	BST(BST* a, BST* b, BST* c, int x) {
		left = a;
		right = b;
		father = c;
		data = x;
	}
	BST() :BST(nullptr, nullptr, nullptr, 0){}
	void DeleteNode(BST* begin, int x);
};

int width,height;

int DeepTree(BST *T)
{
    if(!T)
    {
        return 0;
    }
    return DeepTree(T->left)>DeepTree(T->right)?DeepTree(T->left)+1:DeepTree(T->right)+1;
//�ؼ�����:����ýڵ����������ȴ���������������������ȼ�һ����,�������ֵ�����Ըýڵ������ڵ���������,��������ȴ�ʱ���෴
}

void fillArray(BST *T, char *a,int i, int j)
{
    int ti,tj;
    if(T) //�����λ���нڵ�
    {
		string str = to_string(T->data);
		int t = 0;
		while(t<str.length()){*(a+(i*width)+j+t) = (str[t++]);} //������õ������ַ�
        if(T->left) //�����Һ��Ӹ���Ӧ��������,���Һ��ӵ�ֵ����һ��ݹ鸳
        {
            //���õ���������֮�������ȫ������'/'
            for(ti=i+1,tj=j-1;tj>j-(height-i+1)/2;tj--)
            {
                *(a+((ti)*width)+tj) = -1;
                ti++;
            }
        }
        if(T->right)
        {
            for(ti=i+1,tj=j+1;tj<j+(height-i+1)/2;tj++)
            {
                *(a+((ti)*width)+tj) = 1;
                ti++;
            }
        }
        //����ѭ��,tiǡ��ָ���亢�����ڵĲ�
        fillArray(T->left, a, ti, j-(height-i+1)/2);
        fillArray(T->right, a, ti, j+(height-i+1)/2);
    }
}
void printBiTree(BST *T)
{
    int i,j;
    int n = DeepTree(T); //��������n
    //�ڼ�����������Զ�������ʽ�洢,����һ����������1λ���൱�ڳ���2��1�η�
    width = (2<<n)-3;  // 2^(n+1)-3
    height = (2<<(n-1))-1; // 2^n-1
    char *a = (char *)malloc(sizeof(char) * (width*height+10*width)); // ����ռ�
 
    // �ռ��ʼ��Ϊ0
    for(i=0;i<height;i++)
    {
        for(j=0;j<width+10;j++)
        {
            *(a+(i*width + 10*i)+j) = 0;
        }
    }
 
    //����֮ǰ����õĺ���,����ӡ����
    fillArray(T, a, 0, (width-1)/2);
 
    //���ݴ�ӡ�����������ʵ�ִ�ӡ
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            if(*(a+(i*width)+j) == -1)
            {
                printf("/");
            }else if(*(a+(i*width)+j) == 1)
            {
                printf("\\");
            }else if(*(a+(i*width)+j) == 0)
            {
                printf(" ");
            }else
            {
                printf("%c", *(a+(i*width)+j));
            }
        }
        printf("\n");
    }
}