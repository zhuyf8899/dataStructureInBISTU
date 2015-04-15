//
//  main.cpp
//  GoodsManage
//
//  Created by zhuyifan on 14-5-25.
//  Copyright (c) 2014年 cn.zhuyifan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
//#include <conio>


#define _FILENAME_ "goodsdata.txt"

using namespace std;

const char pw_[60] = "123";

typedef struct _Node
{	int kind;
	char model[20];
	char brand[20];
	int weight;
	int value;
	int amount;
	char date[20];
	char factory[20];
	struct _Node *next = nullptr;
}Node, *LinkList;


int test(){
    int i=9;
    string data;
    fstream te;
    te.open("/Users/zyf/projects/GoodsManage/GoodsManage/goodsdata.txt",ios::in);
    te>>i;
    te>>data;
    cout<<data;
    cout<<i<<endl;
    //te>>data;
    te.close();
    return 1;
}

//读文件
int CreatL(LinkList link){
    fstream fin;
    int counter = 0;
    Node *p = link;
    fin.open("/Users/zyf/projects/GoodsManage/GoodsManage/goodsdata.txt",ios::in);
    while (!fin.eof()) {
    //for(int i=0;i<4;i++){
        Node *temp = (Node*)malloc(sizeof(Node));
        fin>>temp->kind>>temp->model>>temp->brand>>temp->weight>>temp->value>>temp->amount>>temp->date>>temp->factory;
        temp->next = nullptr;
        p->next = temp;
        p = p->next;
        counter++;
    }
    fin.close();
    return counter;
};

//写文件
int SaveL(LinkList link){
    fstream fout_rewrite;
    Node *p = link;
    p = p->next;
    fout_rewrite.open("/Users/zyf/projects/GoodsManage/GoodsManage/goodsdata.txt",ios::out);
    while(p){
        fout_rewrite<<endl;
        fout_rewrite<<p->kind<<" ";
        fout_rewrite<<p->model<<" ";
        fout_rewrite<<p->brand<<" ";
        fout_rewrite<<p->weight<<" ";
        fout_rewrite<<p->value<<" ";
        fout_rewrite<<p->amount<<" ";
        fout_rewrite<<p->date<<" ";
        fout_rewrite<<p->factory;
        p = p->next;
    }
    fout_rewrite.close();
    return 1;
    
};

void search(LinkList l, int number){
    Node *p = l;
    cout<<"查找中..."<<endl;
    cout<<"==============================================================================="<<endl;
    cout<<" 类型  商品名称       品牌     重量 单价 数量        进货日期         产地"<<endl;

    while (p) {
        if (p->kind == number) {
            cout.width(3);
            cout.fill(' ');
            cout<<p->kind;
            cout.width(10);
            cout.fill(' ');
            cout<<p->model;
            cout.width(15);
            cout.fill(' ');
            cout<<p->brand;
            cout.width(3);
            cout.fill(' ');
            cout<<p->weight;
            cout.width(6);
            cout.fill(' ');
            cout<<p->value;
            cout.width(4);
            cout.fill(' ');
            cout<<p->amount;
            cout.width(15);
            cout.fill(' ');
            cout<<p->date;
            cout.width(15);
            cout.fill(' ');
            cout<<p->factory<<endl;;
        }
        p = p->next;
    }
    
    cout<<"===========================查找完成===========================";
    return;
};

void search(LinkList l,char *name){
    Node *p = l;
    cout<<"查找中..."<<endl;
    cout<<"==============================================================================="<<endl;
    cout<<" 类型  商品名称       品牌     重量 单价 数量        进货日期         产地"<<endl;
    while (p) {
        if(!strcmp(p->model,name)){
            cout.width(3);
            cout.fill(' ');
            cout<<p->kind;
            cout.width(10);
            cout.fill(' ');
            cout<<p->model;
            cout.width(15);
            cout.fill(' ');
            cout<<p->brand;
            cout.width(3);
            cout.fill(' ');
            cout<<p->weight;
            cout.width(6);
            cout.fill(' ');
            cout<<p->value;
            cout.width(4);
            cout.fill(' ');
            cout<<p->amount;
            cout.width(15);
            cout.fill(' ');
            cout<<p->date;
            cout.width(15);
            cout.fill(' ');
            cout<<p->factory<<endl;;
        }
        p = p->next;
    }
    return;
};

int insert(LinkList link,Node * exp){
    fstream fout_insert;
    fout_insert.open("/Users/zyf/projects/GoodsManage/GoodsManage/input.txt",ios::app);
    Node *p = link;
    int counter = -1;
    while (p->next) {
        p = p->next;
        counter++;
    }
    p->next = exp;
    fout_insert<<exp->model<<" "<<exp->amount<<endl;
    fout_insert.close();
    return 1;
}

//return 0 means no match
//return 1 means match and delete succeed.
int del(LinkList link,char *name){
    Node *p = link;
    Node *q;
    int del_mark = 0;
    while(p->next){
        if((strcmp(name, p->next->model))==0){
            q = p->next;
            //p->next = p->next->next;
            p->next = q->next;
            free(q);
            del_mark = 1;
        }
        p = p->next;
        if (!p) {
            return del_mark;
        }
    }
    return del_mark;
}

//return 0 means not found
//return 1 means sell done
//return -1 means no goods left
int sell(LinkList link,char *name){
    fstream fout_sell;
    fout_sell.open("/Users/zyf/projects/GoodsManage/GoodsManage/sell.txt",ios::app);
    Node *p = link;
    int sell_mark = 0;
    while(p){
        if(!strcmp(name, p->model)){
            if ((p->amount)>0) {
                (p->amount)--;
                sell_mark = 1;
                fout_sell<<p->model<<endl;
            }else{
                sell_mark = -1;
            }
        }
        p = p->next;
    }
    fout_sell.close();
    return sell_mark;
}

void statistic(LinkList link){
    time_t rawtime;
    struct tm * timeinfo;
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    
    //input log
    string name[200];
    string name_temp;
    int quantity[200];
    int quantity_temp;
    int count = 0;
    int modify_flag=0;
    
    //output log
    string model[200];
    string model_temp;
    int amount[200];
    int count_o = 0;
    int sell_flag = 0;
    
    cout<<"当前时间：";
    printf ( "%4d-%02d-%02d %02d:%02d:%02d\n",1900+timeinfo->tm_year, 1+timeinfo->tm_mon,
            timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
   
    fstream fread_innput,fread_sell;
    fread_innput.open("/Users/zyf/projects/GoodsManage/GoodsManage/input.txt",ios::in);
    while (fread_innput>>name_temp>>quantity_temp) {
        modify_flag=0;
        //fread_innput>>name_temp>>quantity_temp;
        for (int i=0; i<count ; i++) {
            if (name[i]==name_temp) {
                quantity[i] += quantity_temp;
                modify_flag = 1;
            }
        }
        if (modify_flag == 0) {
            name[count] = name_temp;
            quantity[count] = quantity_temp;
            count++;
        }
    }
    fread_innput.close();
    fread_sell.open("/Users/zyf/projects/GoodsManage/GoodsManage/sell.txt",ios::in);
    while (fread_sell>>model_temp) {
        sell_flag=0;
        for (int i=0; i<count_o ; i++) {
            if (model[i]==model_temp) {
                amount[i] +=1;
                sell_flag =1;
                break;
            }
        }
        if (sell_flag == 0) {
            model[count_o] = model_temp;
            amount[count_o] = 1;
            count_o++;
        }

    }
    fread_sell.close();
    
    cout<<"-------------------------------------------------"<<endl;
    cout<<"本日进货名单："<<endl;
    for (int i=0; i<count; i++) {
        cout<<name[i]<<":"<<quantity[i]<<endl;;
    }
    cout<<"-------------------------------------------------"<<endl;
    cout<<"本日销售数量："<<endl;
    for (int i=0; i<count_o; i++) {
        cout<<model[i]<<":"<<amount[i]<<endl;
    }
    
}

//input goods.
int input(LinkList l,char *name,int a){
    fstream fout_input;
    fout_input.open("/Users/zyf/projects/GoodsManage/GoodsManage/input.txt",ios::app);
    Node *p = l;
    int state = 0;
    p = p->next;
    while (p) {
        if (strcmp(p->model,name)==0) {
            p->amount += a;
            state++;
            fout_input<<p->model<<" "<<a<<endl;
        }
        p = p->next;
    }
    fout_input.close();
    return state;
}

//退出
int quit(){
    cout<<"退出前请确认存盘，确认退出输入y，返回输入n：";
    char temp;
    cin>>temp;
    if (temp == 'y' || temp == 'Y') {
        exit(0);
    }
    else
        return -1;
}

//print all links to screen.
void printToScreen(LinkList link){
    //char *empty = "\0";
    cout<<"打印中..."<<endl;
    cout<<"==============================================================================="<<endl;
    cout<<" 类型  商品名称       品牌     重量 单价 数量        进货日期         产地"<<endl;
    
    Node *p = link;
    p = p->next;
    while (p) {
        //if (strlen(p->model)!=0) {
        //if(strlen(p->model)!=0){
        //cout.width(0);
        //cout.fill(' ');
        cout.width(3);
        cout.fill(' ');
        cout<<p->kind;
        cout.width(10);
        cout.fill(' ');
        cout<<p->model;
        cout.width(15);
        cout.fill(' ');
        cout<<p->brand;
        cout.width(3);
        cout.fill(' ');
        cout<<p->weight;
        cout.width(6);
        cout.fill(' ');
        cout<<p->value;
        cout.width(4);
        cout.fill(' ');
        cout<<p->amount;
        cout.width(15);
        cout.fill(' ');
        cout<<p->date;
        cout.width(15);
        cout.fill(' ');
        cout<<p->factory<<endl;;
        //}
        p = p->next;
    }
}

//wizard of insert.
void insert_index(LinkList link){
    Node *temp = (Node*) malloc(sizeof(Node));
    cout<<"请输入商品的类型，名称，品牌，重量，单价，数量，进货日期和产地："<<endl;
    cin>>temp->kind>>temp->model>>temp->brand>>temp->weight>>temp->value>>temp->amount>>temp->date>>temp->factory;
    insert(link, temp);
    return;
}

//wizard of search.
void search_index(LinkList link){
    cout<<"请选择查找方式：按商品种类输入a，按商品名称输入b：";
    char choice;
    cin>>choice;
    if (choice == 'a' || choice == 'A') {
        cout<<"请输入商品种类（一个整数）：";
        int kind;
        cin>>kind;
        search(link,kind);
    }else if(choice == 'b' || choice == 'B'){
        cout<<"请输入商品名称（一个字字符串）:";
        char name[20];
        cin>>name;
        search(link,name);
        
    }else{
        return;
    }
    return;
}

//wizard of delete.
void delete_index(LinkList link){
    cout<<"请输入要删除记录商品的名称：";
    char name[20];
    cin>>name;
    int state; //state of delete.
    state = del(link,name);
    if (state) {
        cout<<"删除完成!"<<endl;
    }else{
        cout<<"未找到该商品。"<<endl;
    }
    return;
}

//wizard of sell.
void sell_index(LinkList link){
    cout<<"请输入销售商品的名称：";
    char name[20];
    cin>>name;
    int state;//state of sell
    state = sell(link, name);
    if (state == 0) {
        cout<<"未找到该商品！"<<endl;
    }else if (state == 1){
        cout<<"销售完成！"<<endl;
    }else{
        cout<<"库存不足！"<<endl;
    }
    return;
}

void input_index(LinkList link){
    cout<<"请注意，本进货功能是指往已有的商品记录中增加库存！"<<endl;
    cout<<"请输入商品名称：";
    char name[20];
    cin>>name;
    cout<<"请输入进货数量："<<endl;
    int quantity;
    cin>>quantity;
    int state;
    state = input(link, name, quantity);
    if (state) {
        cout<<"完成！"<<endl;
    }else{
        cout<<"未找到该商品！"<<endl;
    }
    return;
}

//菜单
void showMenu(){
    cout<<"读取菜单...完成！"<<endl;
    cout<<"====================================================="<<endl;
    cout<<"\t1.读取列表/打印库存报表\t"<<endl;
    cout<<"\t2.保存列表\t"<<endl;
    cout<<"\t3.增加记录\t"<<endl;
    cout<<"\t4.查询记录\t"<<endl;
    cout<<"\t5.删除记录\t"<<endl;
    cout<<"\t6.销售\t"<<endl;
    cout<<"\t7.当日统计\t"<<endl;
    cout<<"\t8.进货\t"<<endl;
    cout<<"\t9.退出"<<endl;
    cout<<"====================================================="<<endl;
    
}

//password
void chkPassword(){
    while (true) {
        cout<<"请输入口令：";
        char pw[64],ch;
        int i=0;
        while((ch=getchar()) != '\n')
        {
            pw[i++]=ch;
            //printf("\b"); //后退一格
            //123printf("*");
        }
        pw[i]='\0';
        if (strcmp(pw,pw_)==0) {
            return;
        }else{
            cout<<"错误！"<<endl;
        }
    }
    
}

int main(int argc, const char * argv[])
{
    //cout<<test();
    //exit(3);
    
    chkPassword();
    
    //clean log before a new day.
    fstream fout_clean;
    fout_clean.open("/Users/zyf/projects/GoodsManage/GoodsManage/input.txt",ios::out);
    fout_clean.close();
    fout_clean.open("/Users/zyf/projects/GoodsManage/GoodsManage/sell.txt",ios::out);
    fout_clean.close();
    
    LinkList l;
    l = (Node*)malloc(sizeof(Node));
    int c = CreatL(l);
    cout<<"+++++++++++"<<c<<endl;
    if (l) {
        while (1) {
            showMenu();
            char command;
            cin>>command;
            switch (command) {
                case '1':
                    printToScreen(l);
                    break;
                case '2':
                    SaveL(l);
                    break;
                case '3':
                    insert_index(l);
                    break;
                case '4':
                    search_index(l);
                    break;
                case '5':
                    delete_index(l);
                    break;
                case '6':
                    sell_index(l);
                    break;
                case '7':
                    statistic(l);
                    break;
                case '8':
                    input_index(l);
                    break;
                case '9':
                    quit();
                    break;
                default:
                    break;
            }

        }
    }
    //c = SaveL(l);
    //cout<<test()<<endl;
    return 0;
}

