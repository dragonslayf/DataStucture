/*2023.09.25*/
//����KMP�㷨������û��ʵ��nextVal���飬�ѵ���Ҫ��Next����ĵ��ƹ�ϵ�ϡ�����
//������ʽ���ܸ����Ż�����ȡ���������е�һ����ࡣ
/*2023.09.26*/
//��������е�NextVal�����ԭ�����Ǻ��ѡ�   ����˼����kmp���ڵ�i����ƥ��ʱ����Next[i]������ƥ�䡣��i-1����Next[i-1]��ͬ����˵��i��Next[i] = Next[i-1] + 1����ͬ������i-1��Next[Next[i-1]]����ƥ�䣬ֱ���ҵ���ƥ��i-1λ�õ��Ӵ������Ҳ���
//��֪�����ϵļ���������ô������ġ�
#include<iostream>
#include<string>
using namespace std;

int Next[1000];//NextֵΪ1�����ַ�������λ�ã�Ϊ0��������ָ��Ҳ���ƶ���
void kmp(string s1, string s2);
int mark[100];
int t;
int main(){

    string s1, s2;

    cin >> s1 >> s2;
    int l = s2.length();
    for(int i = 0; i < l; i++)  Next[i] = 0;
    Next[0] = -1;
    for(int i = 0, j = -1; i < l;){ //jʼ����Next[i-1]
        if(j <0 || s2[j] == s2[i]){
            i++, j++;//����i + 1, ����NExt[i + 1] = Next[i] + 1, Next[i]��֤�Ѿ����.
            Next[i] = j;
            if(s2[j] == s2[i]){//���ﱣ֤���������NextVal���飬��֤�˵�ȷ��i��Next[i]���ʱ��i����ƥ����Next[i]Ҳ�ض���ƥ�䡣��ʱֻ�ܹ�Ѱ��Next[Next[i]]�������ƥ���
                Next[i] = Next[j];
            }
        }
        //���￪ʼ���ѵ�
        else{
            j = Next[j]; //������Ѱ����Ϊi + 1��ƥ���Ҫ����λ��i��β���ַ����Ϳ�ͷĳ���ַ���ƥ�䣬��i��j�������˵��i��Next[i]����ȣ�ֻ����i��Next[Next[i]]����ƥ�䡣ֱ���ҵ������Ҳ���(С����)
        }
    }

    kmp(s1, s2);
    for(int i = 0; i < t; i++){
        cout << mark[i] << endl;
    }
}

void kmp(string s1, string s2){
    int p1, p2 = 0;
    while(p1 < s1.length()){
        if(s1[p1] == s2[p2]){
            p1++;
            p2++;
            if(p2 >= s2.length()){
                mark[t++] = p1-p2;
                p2 = 0;
            }
        }
        else{
            if(Next[p2] == -1){
                p1++;
                p2 = 0;
            }
            else{
                p2 = Next[p2];
            }
        }
    }
}