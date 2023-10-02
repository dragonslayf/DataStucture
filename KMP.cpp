/*2023.09.25*/
//初步KMP算法。。。没有实现nextVal数组，难点主要在Next数组的递推关系上。。。
//代码形式还能更加优化，争取做到像书中的一样简洁。
/*2023.09.26*/
//理解了书中的NextVal数组的原理，不是很难。   核心思想是kmp用于当i处不匹配时，用Next[i]处重新匹配。若i-1处和Next[i-1]相同，则说明i处Next[i] = Next[i-1] + 1若不同，则让i-1和Next[Next[i-1]]重新匹配，直到找到能匹配i-1位置的子串或者找不到
//想知道书上的简洁代码是怎么想出来的。
#include<iostream>
#include<string>
using namespace std;

int Next[1000];//Next值为1代表字符串的首位置，为0代表主串指针也需移动。
void kmp(string s1, string s2);
int mark[100];
int t;
int main(){

    string s1, s2;

    cin >> s1 >> s2;
    int l = s2.length();
    for(int i = 0; i < l; i++)  Next[i] = 0;
    Next[0] = -1;
    for(int i = 0, j = -1; i < l;){ //j始终是Next[i-1]
        if(j <0 || s2[j] == s2[i]){
            i++, j++;//这里i + 1, 计算NExt[i + 1] = Next[i] + 1, Next[i]保证已经算出.
            Next[i] = j;
            if(s2[j] == s2[i]){//这里保证算出来的是NextVal数组，保证了当确定i和Next[i]相等时，i处不匹配则Next[i]也必定不匹配。此时只能够寻找Next[Next[i]]找另外的匹配项。
                Next[i] = Next[j];
            }
        }
        //这里开始是难点
        else{
            j = Next[j]; //这里是寻找因为i + 1不匹配后要求以位置i结尾的字符串和开头某个字符串匹配，而i和j处不相等说明i和Next[i]不相等，只能让i和Next[Next[i]]继续匹配。直到找到或者找不到(小于零)
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