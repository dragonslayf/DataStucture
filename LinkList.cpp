//ʵ���˵������ͷ�巨������β�巨��������ʼ����ָ��λ�ò��룬ָ��λ��ɾ���������Ȳ�����
//ʹ����ͷ��㣬������һ���࣬LinkNode, ������ָ������ΪLinkList.����length����ֻ��LinkList����������

//2023.09.18  �ɹ�ʵ���������㷨����solution��������Ӧ��ϰ���ֵ������˼����
#include<iostream>
using namespace std;

template<class ElemType>

class LinkNode{
public:
    ElemType data;
    LinkNode* next;
    
    LinkNode(ElemType d){
        data = d;
        next = nullptr;
    }
    LinkNode():LinkNode(0){}
    int length;
};

template<class ElemType>
using LinkList = LinkNode<ElemType>*;
template<class ElemType>
int InitList(LinkList<ElemType>& L){
    L = new LinkNode<ElemType>();
    L->next = nullptr;
    L->length = 0;
    return 1;
}
template<class ElemType>
int List_HeadInsert(LinkList<ElemType> &L, int n){
    ElemType tmp;
    L->length += n;
    while(n--){
        cin >> tmp;
        LinkList<ElemType> t = new LinkNode<ElemType>(tmp);
        t->next = L->next;
        L->next = t;
    }
    return 1;
}
template<class ElemType>
int List_TailInsert(LinkList<ElemType> &L, int n){
    ElemType tmp;
    L->length += n;
    LinkList<ElemType> r = L;
    while(n--){
        cin >> tmp;
        LinkList<ElemType> t = new LinkNode<ElemType>(tmp);
        r->next = t;
        r = t;
    }
    return 1;
}

template<class ElemType>

int List_Tranverse(LinkList<ElemType> L){
    int l = L->length;
    while(l--){
        L = L->next;
        cout << L->data;
        if(l > 0){cout << " ";}
        else{cout << endl;}
    }
    return 1;
}

template<class ElemType>

ElemType getElem(LinkList<ElemType> L, int i){
    LinkList<ElemType> p = L->next;
    while(p && i--){
        p = p->next;
    }
    if(p == nullptr){return 0;}
    else{
        return p->data;
    }
}

template<class ElemType>

void insert(LinkList<ElemType> &L, ElemType d, int i){
    LinkList<ElemType> t = L;
    while(t && i--){
        t = t->next;
    }
    if(t == nullptr) return;
    L->length++;
    LinkList<ElemType> new_t = new LinkNode<ElemType>(d);
    new_t->next = t->next;
    t->next = new_t;
    return;
}
\
template<class ElemType>

void remove(LinkList<ElemType> &L, int i){
    LinkList<ElemType> t = L;
    while(t && i--){
        t = t->next;
    }
    if(t == nullptr || t->next == nullptr) return;
    L->length--;
    LinkList<ElemType> to_d = t->next;
    t->next = to_d->next;
    delete to_d;
}
template<class ElemType>

void solution(LinkList<ElemType> &L){//���������е�40ҳ��25��
    LinkList<ElemType> p, q, r, s, t;
    p = q = L;
    while(q->next){
        p = p->next;
        q = q->next;
        if(q->next){
            q = q->next;
        }
    }
    //�õ�pΪ�м�ڵ㣬����ǰ��һ���ڵ㡣
    r = p->next;
    s = r->next;
    p->next = q;
    r->next = nullptr;
    while(s){
        t = s->next;
        s->next = r;
        r = s;
        s = t;
    }
    //�������
    //��ʱp��Ľڵ�Ӧ��ȫ���������
    s = L->next;
    t = p->next;
    while(t){
        p = s->next;
        q = t->next;
        t->next = s->next;
        s->next = t;
        s = p;
        t = q;
    }
}
int main(){
    LinkList<int> L;
    InitList(L);
    List_TailInsert(L, 2);
    List_Tranverse(L);
    
    solution(L);
    List_Tranverse(L);
}