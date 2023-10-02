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
//关键代码:如果该节点的左子树深度大于右子树则将左子树的深度加一返回,这个返回值便是以该节点做根节点的树的深度,右子树深度大时则相反
}

void fillArray(BST *T, char *a,int i, int j)
{
    int ti,tj;
    if(T) //如果该位置有节点
    {
		string str = to_string(T->data);
		int t = 0;
		while(t<str.length()){*(a+(i*width)+j+t) = (str[t++]);} //向数组该点填入字符
        if(T->left) //有左右孩子给对应的连接线,左右孩子的值在下一层递归赋
        {
            //将该点与其左孩子之间的连线全部填上'/'
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
        //经过循环,ti恰好指到其孩子所在的层
        fillArray(T->left, a, ti, j-(height-i+1)/2);
        fillArray(T->right, a, ti, j+(height-i+1)/2);
    }
}
void printBiTree(BST *T)
{
    int i,j;
    int n = DeepTree(T); //计算出深度n
    //在计算机中数据以二进制形式存储,所以一个数据左移1位就相当于乘以2的1次方
    width = (2<<n)-3;  // 2^(n+1)-3
    height = (2<<(n-1))-1; // 2^n-1
    char *a = (char *)malloc(sizeof(char) * (width*height+10*width)); // 申请空间
 
    // 空间初始化为0
    for(i=0;i<height;i++)
    {
        for(j=0;j<width+10;j++)
        {
            *(a+(i*width + 10*i)+j) = 0;
        }
    }
 
    //调用之前定义好的函数,填充打印数组
    fillArray(T, a, 0, (width-1)/2);
 
    //根据打印数组的内容来实现打印
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