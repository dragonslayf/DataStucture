#include<iostream>
#include<stack>
using std::stack;
using std::cin;
using std::cout;
using std::endl;
constexpr int MAXSIZE = 10;
class Queue{
    public:
    int front = 0;
    int rear = 0; // 空一位以便区分满和空状态
    int s[MAXSIZE];
    int empty(){
        return front == rear;
    }
    int full(){
        return ((rear + 1) % MAXSIZE) == front;
    }
    void enQueue(int data){
        if(full()){return;}
        s[rear] = data;
        rear = (rear + 1) % MAXSIZE;
    }
    int deQueue(){
        if(empty()) return -1;
        int t = s[front];
        front++;
        return t;
    }
    int getTop(){
        if(empty()) return -1;
        return s[front];
    }
    Queue(){
        ;
    }
};
//实现循环队列

int main(){
    Queue q;
    q.enQueue(3);
    q.enQueue(4);
    q.enQueue(5);
    q.enQueue(6);
    cout << q.deQueue();
    cout << q.deQueue();
    cout << q.deQueue();
    q.enQueue(6);
    q.enQueue(9);
    cout << q.deQueue();
    cout << q.deQueue();


}