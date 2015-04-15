//
//  main.cpp
//  Parking
//
//  Created by zhuyifan on 14-5-26.
//  Copyright (c) 2014年 cn.zhuyifan. All rights reserved.
//

#include <iostream>
#include <time.h>
using namespace std;

const int size = 10;

typedef struct{
    //几点说明：
    //由于车牌号和时刻都是整数型的，那么，车牌号定义为独一无二的编号，时间定为4位长的整数以表示相应的时间
    int carnumber;  //车号
    //int time;        //汽车“到”或“离”的时刻
    time_t time;
}Car;

typedef struct{
	Car *base;
	Car *top;
	int stacksize;
}SqStack;

typedef struct QNode{
	Car data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//init the stack which is used as a garage.
Car* InitStack(SqStack &stack){
    stack.top=stack.base = (Car*)malloc(sizeof(Car)*size);
    stack.stacksize = 0;
    return stack.base;
}

//push into stack as car parking（without time marking)
int Push(SqStack &stack,Car e){
    if (stack.stacksize>=10) {
        return -1;
    }
    *stack.top = e;
    
    stack.top++;
    stack.stacksize++;
    return 1;
}

int Pop(SqStack &stack,Car &e){
    if (stack.stacksize<=0) {
        return -1;
    }
    stack.top--;
    e = *stack.top;
    stack.stacksize--;
    return 1;
}

//init the queue whick is used as BIANDAO
QNode * InitQueue(LinkQueue &Q){
    Q.front=Q.rear=(QNode*)malloc(sizeof(QNode));
    return Q.rear;
}

//
int EnQueue(LinkQueue &Q,QNode *e){
    if (Q.front == Q.rear && Q.front->data.carnumber==0) {
        Q.front = e;
        Q.rear = e;
    }else{
        Q.rear->next = e;
        Q.rear = e;
    }
    return 1;
}

QNode * DeQueue(LinkQueue &Q){
    QNode *temp = Q.front;
    Q.front = Q.front->next;
    return temp;
}

int sizeOfQueue(LinkQueue &Q){
    QNode *p = Q.front;
    int counter = 0;
    while (p && p->data.carnumber!=0) {
        counter++;
        p = p->next;
    }
    return counter;
}

//return 1 means push into stack successfully.
//return 2 means enter the queue.
int CarArrical(SqStack &stack,LinkQueue &queue,Car acar){
    time(&acar.time);
    int state_stack = Push(stack, acar);
    if (state_stack == -1) {
        QNode *c = (QNode*)malloc(sizeof(QNode));
        c->data = acar;
        c->next = nullptr;
        EnQueue(queue, c);
        return 2;
    }
    return 1;
}

void showStack(SqStack &stack){
    Car * currptr = stack.base;
    cout<<"___这个是车库底部___"<<endl;
    while(currptr != stack.top){
        cout<<"|  "<<currptr->carnumber<<"  |"<<endl;
        currptr++;
    }
}

void showQueue(LinkQueue &queue){
    QNode *currptr = queue.front;
    cout<<"front| ";
    if (sizeOfQueue(queue)) {
        while (currptr != queue.rear) {
            cout<<currptr->data.carnumber<<" |";
            currptr = currptr->next;
        }
        cout<<currptr->data.carnumber<<"  |";
    }
    cout<<"|"<<endl;
    return;
    
}

int CarLeave(SqStack &fom,SqStack &bac,LinkQueue &queue,int number){
    int flag_inFormat = 0;
    Car * chkptr = fom.base;
    int counter = 0;
    while (chkptr != fom.top) {
        if (chkptr->carnumber == number) {
            Car * locate_ptr = chkptr;
            while (locate_ptr != fom.top) {
                locate_ptr++;
                counter++;
                //此时，counter记录了包括要出栈的那辆车以内的要挪窝的车的个数
            }
            flag_inFormat = 1;
        }
        chkptr++;
    }
    if (flag_inFormat == 0) {
        return 0;
    }else{
        //开始挪窝
        Car exchange;
        for (int i=0; i<(counter-1); i++) {
            Pop(fom, exchange);
            Push(bac, exchange);
        }
        cout<<"此车停靠在车库深处，需要将它之前的"<<counter-1<<"辆车先移出停入临时车库，移动后临时车库的情况为："<<endl;
        showStack(bac);
        Pop(fom, exchange);
        //
        time_t current = time(&current);
        cout<<"牌号为"<<exchange.carnumber<<"的车停车时间为："<<(current-exchange.time)<<endl;
        //
        for (int i=0; i<counter-1; i++) {
            Pop(bac, exchange);
            Push(fom, exchange);
        }
        
        //检查便道队列是否有车
        if (sizeOfQueue(queue)) {
            QNode *p = DeQueue(queue);
            //queue.front = queue.front->next;
            Push(fom, p->data);
        }
    }
    return 1;
}

int quit(){
    cout<<"确定退出请输入Y，返回请输入N："<<endl;
    char c;
    cin>>c;
    if (c == 'Y' || c == 'y') {
        exit(1);
    }else{
        return 1;
    }
    return -1;
}

void preFunctionIn(SqStack &s,LinkQueue &q,int num){
    cout<<"加载预定预定义功能中..."<<endl;
    Car acar;
    for(int i=1;i<=num;i++) {
        acar.carnumber=i;
        CarArrical(s, q, acar);
    }
    cout<<"加载完成！"<<endl;
    return;
}

void parking_index(SqStack &s,LinkQueue &q){
    cout<<"请输入车牌号：";
    int number;
    cin>>number;
    Car acar;
    acar.carnumber = number;
    int state = CarArrical(s, q, acar);
    if (state == 1) {
        cout<<"牌号为"<<number<<"的车辆进入车库成功。"<<endl;
    }else if (state == 2){
        cout<<"车库已满，牌号为"<<number<<"的车辆进入便道等待。"<<endl;
    }else{
        cout<<"kernel error."<<endl;
    }
    return;
}

void leaving_index(SqStack &s,SqStack &b,LinkQueue &q){
    cout<<"请输入车牌号：";
    int number;
    cin>>number;
    int state = CarLeave(s, b, q, number);
    if (state == 0) {
        cout<<"这辆车不在车库中（它可能在便道上或者根本不存在）。"<<endl;
    }else if (state == 1){
        cout<<"车辆离开。"<<endl;
    }
    return;
}

int main(int argc, const char * argv[])
{
    SqStack format;
    SqStack backup;
    InitStack(format);
    InitStack(backup);
    LinkQueue ahead;
    InitQueue(ahead);
//    Car acar;
//    for(int i=1;i<=13;i++) {
//        acar.carnumber=i;
//        acar.time=1000+1;
//        CarArrical(format, ahead, acar);
//    }
//    
//
//    CarLeave(format, backup, ahead,5);
//    CarLeave(format, backup, ahead, 6);
//    CarLeave(format, backup, ahead, 6);
//    CarLeave(format, backup, ahead, 7);
//    CarLeave(format, backup, ahead, 1);
//    showStack(format);
//    showQueue(ahead);
    while (1) {
        cout<<"======================================================"<<endl;
        cout<<"              欢迎使用停车模拟程序，请选择功能："<<endl;
        cout<<"      1.展示当前车库中的停放情况"<<endl;
        cout<<"      2.展示当前便道中的停放情况"<<endl;
        cout<<"      3.停车入库"<<endl;
        cout<<"      4.车辆出库"<<endl;
        cout<<"      5.预定义功能a：连续停放15辆车(车牌号1-15)"<<endl;
        cout<<"      6.预定义功能b：连续停放10辆车(车牌号1-10)"<<endl;
        cout<<"      7.退出"<<endl;
        cout<<"======================================================"<<endl;
        int command;
        cin>>command;
        switch (command) {
            case 1:
                showStack(format);
                break;
            case 2:
                showQueue(ahead);
                break;
            case 3:
                parking_index(format,ahead);
                break;
            case 4:
                leaving_index(format,backup,ahead);
                break;
            case 5:
                preFunctionIn(format,ahead,15);
                break;
            case 6:
                preFunctionIn(format,ahead,10);
                break;
            case 7:
                quit();
                break;
            default:
                cout<<"无效的命令!"<<endl;
                break;
        }
    }
    return 0;
}

