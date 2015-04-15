//
//  main.cpp
//  StudentManage
//
//  Created by zhuyifan on 14-6-8.
//  Copyright (c) 2014年 cn.zhuyifan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
const string filePath = "/Users/zyf/projects/StudentManage/StudentManage/st.dat";
const int numberOfStudent = 100;
int counterOfNum = 0;

struct Student //结构体
{
    int term;//学期
    int num;//学号
    string name;//姓名
    float mark1;//数据结构成绩
    float mark2;//操作系统成绩
    float mark3;//微机成绩
    float sum;//总分
    float average;//平均分
};

//-1 means file is too big that memory cannot read all of them.
//1 means the memory is fully used.
//2 means we read less persons than the memory.
int readFromFile(Student example[])
{
    counterOfNum = 0;
    ifstream finFromFile(filePath,ios::in);
    int i = 0;
    while (finFromFile>>example[i].term>>example[i].num>>example[i].name>>example[i].mark1>>example[i].mark2>>example[i].mark3>>example[i].sum>>example[i].average) {
        i++;
        counterOfNum++;
        if (i>=numberOfStudent) {
            finFromFile.close();
            return -1;
        }
    }
    finFromFile.close();
    if (i == 49) {
        return 1;
    }
    return 2;
}

int saveToFile(Student example[])
{
    ofstream fout(filePath,ios::out);
    int i = 0;
    for (i = 0; i<counterOfNum; i++) {
        if (example[i].term) {
            fout<<example[i].term<<" ";
            fout<<example[i].num<<" ";
            fout<<example[i].name<<" ";
            fout<<example[i].mark1<<" ";
            fout<<example[i].mark2<<" ";
            fout<<example[i].mark3<<" ";
            fout<<example[i].sum<<" ";
            fout<<example[i].average<<endl;
        }else
            break;
        
    }
    return 1;
}

void printToScreen(Student example[]){
    cout<<"=================================================================="<<endl;
    cout<<"学期    学号    姓名        成绩1  成绩2  成绩3       总分      平均"<<endl;
    for (int i = 0; i<counterOfNum; i++) {
        if (example[i].num) {
            cout.width(3);
            cout.fill(' ');
            cout<<example[i].term;
            cout.width(10);
            cout.fill(' ');
            cout<<example[i].num;
            cout.width(10);
            cout.fill(' ');
            cout<<example[i].name;
            cout.width(6);
            cout.fill(' ');
            cout<<example[i].mark1;
            cout.width(6);
            cout.fill(' ');
            cout<<example[i].mark2;
            cout.width(6);
            cout.fill(' ');
            cout<<example[i].mark3;
            cout.width(10);
            cout.fill(' ');
            cout<<example[i].sum;
            cout.width(18);
            cout.fill(' ');
            cout<<example[i].average<<endl;
        }
    }
    cout<<"----------------------------------------------------------------"<<endl;
}

//1 means all ok.
//-1 means the array is full.
int insertStudent(Student example[],Student one){
    if (counterOfNum>=numberOfStudent) {
        return -1;
    }
    example[counterOfNum] = one;
    counterOfNum++;
    return 1;
}

void wizardOfInsert(Student example[])
{
    Student one;
    cout<<"请依次输入学期，学号，姓名，成绩1，成绩2，成绩3，用空格分开，输入完成请回车."<<endl;
    cout<<":";
    cin>>one.term>>one.num>>one.name>>one.mark1>>one.mark2>>one.mark3;
    one.sum = (one.mark1+one.mark2+one.mark3);
    one.average = one.sum/3;
    if (insertStudent(example, one) == 1) {
        cout<<"插入完成."<<endl;
        return;
    }
    cout<<"insert error."<<endl;
    return;
}

//1 means delete at least one data.
//0 means delete none.
int deleteStudent(Student example[],string name)
{
    int del_flag = 0;
    for (int i=0; i<counterOfNum; i++) {
        if (example[i].name == name) {
            int j=i+1;
            for (; j<counterOfNum; j++) {
                example[j-1]=example[j];
            }
            del_flag = 1;
            counterOfNum--;
        }
    }
    return del_flag;
}

//1 means delete at least one data.
//0 means delete none.
int deleteStudent(Student example[],int num)
{
    int del_flag = 0;
    for (int i=0; i<counterOfNum; i++) {
        if (example[i].num == num) {
            int j=i+1;
            for (; j<counterOfNum; j++) {
                example[j-1]=example[j];
            }
            del_flag = 1;
            counterOfNum--;
        }
    }
    return del_flag;
}

void wizardOfDelete(Student example[])
{
    int command;
    cout<<"请选择索引种类，1为姓名，2为学号：";
    cin>>command;
    if (command ==1) {
        cout<<"请输入姓名：";
        string n;
        cin>>n;
        if (deleteStudent(example, n)) {
            cout<<"删除成功."<<endl;
        }else{
            cout<<"未查找到该人"<<endl;
        }
    }else if(command == 2){
        cout<<"请输入学号：";
        int n;
        cin>>n;
        if (deleteStudent(example, n)) {
            cout<<"删除成功."<<endl;
        }else{
            cout<<"未查找到该人"<<endl;
        }
    }else{
        cout<<"bad command."<<endl;
    }
    return;
}

//renturn value means find&changed the number of issue.
int changeStudent(Student example[],Student *one)
{
    int change_flag = 0;
    for (int i = 0; i<counterOfNum; i++) {
        if (example[i].num == one->num) {
            example[i] = *one;
        }
        change_flag++;
    }
    return change_flag;
}

void wizardOfChange(Student example[])
{
    cout<<"请输入要修改的学号:";
    int number;
    cin>>number;
    Student *one = new Student;
    cout<<"请依次输入学期，学号，姓名，成绩1，成绩2，成绩3，用空格分开，输入完成请回车."<<endl;
    cout<<":";
    cin>>one->term>>one->num>>one->name>>one->mark1>>one->mark2>>one->mark3;
    one->sum = (one->mark1+one->mark2+one->mark3);
    one->average = one->sum/3;
    //
    //
    //
    if(changeStudent(example, one)==0)
        cout<<"未找到！"<<endl;
    else
        cout<<"修改完成."<<endl;
    return;
}

void searchPrint(Student example[])
{
    cout<<"请输入要查找的姓名或学号：";
    string test;
    cin>>test;
    int te = atoi(test.c_str());
    for (int i =0; i<counterOfNum; i++) {
        if (te==example[i].num || test ==example[i].name) {
            cout<<"发现一条-->"<<endl;
            cout.width(3);
            cout.fill(' ');
            cout<<example[i].term;
            cout.width(10);
            cout.fill(' ');
            cout<<example[i].num;
            cout.width(10);
            cout.fill(' ');
            cout<<example[i].name;
            cout.width(6);
            cout.fill(' ');
            cout<<example[i].mark1;
            cout.width(6);
            cout.fill(' ');
            cout<<example[i].mark2;
            cout.width(6);
            cout.fill(' ');
            cout<<example[i].mark3;
            cout.width(6);
            cout.fill(' ');
            cout<<example[i].sum;
            cout.width(6);
            cout.fill(' ');
            cout<<example[i].average<<endl;

        }
    }
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    return;
}

//type:
//1 means order by xuehao
//2 means order by name
//3 means order by mark1
//4 means order by mark2
//5 means order by mark3
//6 means order by sum/average.
void sortSelect(Student original[],int type)
{
    Student temp;
    int max;
    if (type == 1) {
        int max;
        for (int i=0; i<counterOfNum-1; i++) {
            max = i;
            for (int j=i+1; j<counterOfNum; j++) {
                if (original[max].num>original[j].num) {
                    max = j;//min actully
                }
                
            }
            if (max != i) {
                temp = original[i];
                original[i] = original[max];
                original[max] = temp;
            }
        }
        
    }else if(type ==2) {
        for (int i=0; i<counterOfNum-1; i++) {
            max = i;
            for (int j=i+1; j<counterOfNum; j++) {
                if (original[max].name>original[j].name) {
                    max = j;//min actully
                }
                
            }
            if (max != i) {
                temp = original[i];
                original[i] = original[max];
                original[max] = temp;
            }
        }
    }else if(type ==3){
        for (int i=0; i<counterOfNum-1; i++) {
            max = i;
            for (int j=i+1; j<counterOfNum; j++) {
                if (original[max].mark1<original[j].mark1) {
                    max = j;
                }
                
            }
            if (max != i) {
                temp = original[i];
                original[i] = original[max];
                original[max] = temp;
            }
        }
    }
    else if(type ==4){
        for (int i=0; i<counterOfNum-1; i++) {
            max = i;
            for (int j=i+1; j<counterOfNum; j++) {
                if (original[max].mark3<original[j].mark3) {
                    max = j;
                }
                
            }
            if (max != i) {
                temp = original[i];
                original[i] = original[max];
                original[max] = temp;
            }
        }
    }
    else if(type ==5){
        for (int i=0; i<counterOfNum-1; i++) {
            max = i;
            for (int j=i+1; j<counterOfNum; j++) {
                if (original[max].mark3<original[j].mark3) {
                    max = j;
                }
                
            }
            if (max != i) {
                temp = original[i];
                original[i] = original[max];
                original[max] = temp;
            }
        }
    }
    else if(type ==6){
        for (int i=0; i<counterOfNum-1; i++) {
            max = i;
            for (int j=i+1; j<counterOfNum; j++) {
                if (original[max].sum<original[j].sum) {
                    max = j;
                }
                
            }
            if (max != i) {
                temp = original[i];
                original[i] = original[max];
                original[max] = temp;
            }
        }
    }
}

//type:
//1:id
//2:sun/average
void sortBubble(Student example[],int type)
{
    Student temp;
    if (type==1) {
        for (int j=0; j<counterOfNum-1; j++) {
            for (int i=0; i<counterOfNum-1-j; i++) {
                if (example[i].num>example[i+1].num) {
                    temp = example[i];
                    example[i]=example[i+1];
                    example[i+1]=temp;
                }
            }
        }
    }else if(type ==2){
        for (int j=0; j<counterOfNum-1; j++) {
            for (int i=0; i<counterOfNum-1-j; i++) {
                if (example[i].sum<example[i+1].sum) {
                    temp = example[i];
                    example[i]=example[i+1];
                    example[i+1]=temp;
                }
            }
        }
    }
    return;
}

void showMenu()
{
    cout<<"==============================="<<endl;
    cout<<"\t1.查看所有名单"<<endl;
    cout<<"\t2.增加学生"<<endl;
    cout<<"\t3.删除学生"<<endl;
    cout<<"\t4.改动学生"<<endl;
    cout<<"\t5.查找学生"<<endl;
    cout<<"\t6.存盘"<<endl;
    cout<<"\t7.选择排序"<<endl;
    cout<<"\t8.冒泡排序"<<endl;
    cout<<"\t9.退出"<<endl;
    cout<<"==============================="<<endl;
    return;
    
}

//type_:
//1:select
//2.bubble
void wizardOfSort(Student example[],int type_)
{
    if (type_ == 1) {
        cout<<"请输入排序种类，"<<endl;
        cout<<"1->按学号排序，升序"<<endl;
        cout<<"2->按姓名排序，升序"<<endl;
        cout<<"3->按成绩1排序，降序"<<endl;
        cout<<"4->按成绩2排序，降序"<<endl;
        cout<<"5->按成绩3排序，降序"<<endl;
        cout<<"6->按总分、平均分排序，降序"<<endl;
        cout<<"^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
        cout<<":";
        int request;
        cin>>request;
        sortSelect(example,request);
        printToScreen(example);
    }else if(type_==2){
        cout<<"请输入排序种类，"<<endl;
        cout<<"1->按学号排序，升序"<<endl;
        cout<<"2->按总成绩/平均分排序，降序"<<endl;
        cout<<"^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
        cout<<":";
        int request;
        cin>>request;
        sortSelect(example,request);
        printToScreen(example);
    }
    
    return;
}

void wizardToExit()
{
    cout<<"确定退出吗？（y/n）:";
    char x;
    cin>>x;
    if (x=='y'||x=='Y') {
        exit(1);
    }
    return;
}

int main(int argc, const char * argv[])
{

    Student stu[numberOfStudent];
    readFromFile(stu);
    cout<<counterOfNum;
    while (1) {
        showMenu();
        int re;
        cin>>re;
        switch (re) {
            case 1:
                printToScreen(stu);
                break;
            case 2:
                wizardOfInsert(stu);
                break;
            case 3:
                wizardOfDelete(stu);
                break;
            case 4:
                wizardOfChange(stu);
                break;
            case 5:
                searchPrint(stu);
                break;
            case 6:
                saveToFile(stu);
                break;
            case 7:
                wizardOfSort(stu,1);
                break;
            case 8:
                wizardOfSort(stu,2);
                break;
            case 9:
                wizardToExit();
                break;
            default:
                break;
        }
    }
    
    
    
    return 0;
}

