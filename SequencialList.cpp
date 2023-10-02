//线性表的实现，实现了插入和删除的功能

#include<iostream>

using namespace std;
#define MAXSIZE 500
template<class element>

class SqList{
    public:
    element* t;
    int length;
    SqList(){
        t = new element[MAXSIZE];
        length = 0;
    }
    int InsertList(int i, element e){
        if(i < 0 || i > length){
            return 0;
        }
        for(int j = length - 1; j >= i; j--){
            t[j+1] = t[j];
        }
        t[i] = e;
        length++;
        return 1;
    }   
    int RemoveList(int i){
        if(i < 0 || i >= length){
            return 0;
        }
        for(int j = i + 1; j < length; j++){
            t[j-1] = t[j];
        }
        length--;
        return 1;
    }
};

int main(){
    SqList<int> L;
    L.InsertList(0, 2);
    L.InsertList(1, 3);
    L.InsertList(2, 4);
    L.InsertList(2, 6);
    L.InsertList(6, 2);
    L.InsertList(-1, 2);
    L.RemoveList(2);
    for(int i = 0; i < L.length; i++){
        cout << L.t[i] << endl;
    }
    cout << "The length is: " << L.length << endl;
}