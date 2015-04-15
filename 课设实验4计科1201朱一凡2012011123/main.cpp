#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

const int n=13;
//const int max = 32767;
#define max 32767

struct Node
{
	string num;
	string name;
};

class graph
{
public:
	graph();
	void floyd();
	void search();
	void all();
	void print();
	void show();
private:
	Node v[n+1];
	int arcs[n+1][n+1];
	int a[n+1][n+1];
	int path[n+1][n+1];
};


//构造函数
//默认生成13个节点，之间的关系如下所示：
/*//


       |  A1  |  B2  |  C3  |  D4  |  E5 |  F6  |  G7  |  H8  |  I9  |  J10  |  K11  |  L12  |  M13   |
   A1  |  0   | 120  |
   B2  | 120  |   0  |  70  |      |  90 |
   C3  |      |  70  |   0  | 100  |  40 |  60  |  80  |
   D4  |      |      | 100  |   0  |     |      |  80  |
   E5  |      |  90  |  40  |      |   0 |  50  |      |  90  |
   F6  |      |      |  60  |      |  50 |   0  |  30  |  90  |  80  |
   G7  |      |      |  80  |  80  |     |  30  |   0  |      |  70  |
   H8  |      |      |      |      |  90 |  90  |      |      | 100  |   30  |
   I9  |      |      |      |      |     |  80  |  70  |  100 |   0  |  110  |       |  190  |
   J10 |      |      |      |      |     |      |      |  30  | 110  |    0  |   50  |  100  |
   K11 |      |      |      |      |     |      |      |      |      |   50  |    0  |       |   50   |
   L12 |      |      |      |      |     |      |      |      | 190  |  100  |       |    0  |   80   |
   M13 |      |      |      |      |     |      |      |      |      |       |   50  |   80  |    0   |
//*/
graph::graph()
{
	v[1].name="一柱擎天";
	v[2].name="二龙戏珠";
	v[3].name="三顾茅庐";
	v[4].name="四面楚歌";
	v[5].name="五福临门";
	v[6].name="六月飞霜";
	v[7].name="七行俱下";
	v[8].name="八音迭奏";
	v[9].name="九九归一";
	v[10].name="十面埋伏";
	v[11].name="百川归海";
	v[12].name="千山万壑";
	v[13].name="万家灯火";
	v[1].num="A";
	v[2].num="B";
	v[3].num="C";
	v[4].num="D";
	v[5].num="E";
	v[6].num="F";
	v[7].num="G";
	v[8].num="H";
	v[9].num="I";
	v[10].num="J";
	v[11].num="K";
	v[12].num="L";
	v[13].num="M";
    //..........以二维数组存储邻接矩阵.....................
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i==j)
				arcs[i][j]=0;//对角线的位置不就是自己到自己么，所以为0
			else
				arcs[i][j]=32767;//其他位置都是32767
	arcs[1][2]=120;//逐个设置路径值:这是一个无向图
	arcs[2][1]=120;
	arcs[2][3]=70;
	arcs[2][5]=90;
	arcs[3][2]=70;
	arcs[3][4]=100;
	arcs[3][5]=40;
	arcs[3][6]=60;
	arcs[3][7]=80;
	arcs[4][3]=100;
	arcs[4][7]=80;
	arcs[5][6]=50;
	arcs[5][3]=40;
	arcs[5][2]=90;
	arcs[5][8]=90;
	arcs[6][3]=60;
	arcs[6][5]=50;
	arcs[6][7]=30;
	arcs[6][8]=90;
	arcs[6][9]=80;
	arcs[7][3]=80;
	arcs[7][4]=80;
	arcs[7][9]=70;
	arcs[7][6]=30;
	arcs[8][6]=90;
	arcs[8][9]=100;
	arcs[8][10]=30;
	arcs[8][5]=90;
	arcs[9][6]=80;
	arcs[9][7]=70;
	arcs[9][8]=100;
	arcs[9][10]=110;
	arcs[9][12]=190;
	arcs[10][8]=30;
	arcs[10][9]=110;
	arcs[10][12]=100;
	arcs[10][11]=50;
	arcs[11][10]=50;
	arcs[11][13]=50;
	arcs[12][9]=190;
	arcs[12][10]=100;
	arcs[12][13]=80;
	arcs[13][11]=50;
	arcs[13][12]=80;
	floyd();//调用这个算法 ，求path
    
}
//输出所有的景点代号和名称对照
void graph::print()//打印号码和名称
{
	cout<<"\t"<<setiosflags(ios_base::left)<<setw(10)<<"代号"<<"名称"<<endl;
    
	for(int i=1;i<=n;i++)
		cout<<"\t"<<setw(10)<<v[i].num<<v[i].name<<endl;
}


//floyd算法
void graph::floyd()//标准的floyd算法
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			a[i][j]=arcs[i][j];
			if((i!=j)&&(a[i][j]<max))
				path[i][j]=i;
			else
				path[i][j]=0;
		}
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(a[i][k]+a[k][j]<a[i][j])
                {
                    a[i][j]=a[i][k]+a[k][j];
                    path[i][j]=path[k][j];
                }
        
    }
}

//遍历整个图的算法
void graph::all()
{
	string point;
	int begin;  //整形 开始begin
    begin=0;    //begin初值为0
	print();    //打印
	cout<<"\n\t请输入您所在位置：";
	cin>>point;
	cout<<"\n";
	for(int i=1;i<=n;i++)//n=13
	{
		if(point==v[i].name)
			begin=i;
		else if(point==v[i].num)
			begin=i;
	}
    
    if(begin==0)
    {
        cout<<"\t\t找不到这个地点！"<<endl;
        return;
    }
    else
    {
        for(int j=1;j<=n;j++)
        {
            if(begin!=j)
            {
                int next=path[j][begin];//我们以D到E为例，D-C-E是路径，D是4 C是3 E是5,那么begin就是4，此时的j循环到5，
                //就是path[5][4],由图的关系我们知道这个数是3，则next就是3
                cout<<v[begin].num<<"("<<v[begin].name<<")";//先打印出，D的号和名字
                while(next!=j)//刚才那个数3（next）不是终点j的时候
                {
                    cout<<"==>"<<v[next].num<<"("<<v[next].name<<")";//把这个3号信息也就是C信息的序号和名字打出来
                    next=path[j][next];//由floyd算法，这时的next是5，于是就没有下一次的while循环了 跳出进入下一步
                    
                }
                cout<<"==>"<<v[j].num<<"("<<v[j].name<<")"<<endl;//把5号信息打出来
            }
        }
    }
}

//查找函数，利用字符串比较函数进行查找
void graph::search()
{
    int begin,over;
    //char starts[20],ends[20];
    char choose;
    //choose1,choose2;
    string start,end,starts,ends;
    begin=0;
    over=0;
    print();
    cout<<endl;
    cout<<"\t1.按代号查询"<<endl;
    cout<<"\t2.按名称查询"<<endl;
    cout<<"\t请输入您要选择的查询方式：";
    cin>>choose;
    switch(choose)
    {
		case '1':
        {
            cout<<endl;
			cout<<"\t请输入起点：";
			cin>>start;
			cout<<"\t请输入终点：";
			cin>>end;
			for(int i=1;i<=n;i++)
				if(start==v[i].num)
					begin=i;
            for(int i=1;i<=n;i++)
                if(end==v[i].num)
                    over=i;
            if(begin==0||over==0)
            {
                cout<<"\t\t做不到！对不起！！"<<endl;
                break;
            }
            if(begin!=over)//如果起点和终点不一样则 ,,这个方法和上面那个方法类似，比上面的还要简单，道理一样
            {
                cout<<v[begin].num<<"("<<v[begin].name<<")";//打印出起始点字母和起始名
                int next=path[over][begin];
                while(next !=over)//下一个不是结束点的时候
                {
                    cout<<"-->"<<v[next].num<<"("<<v[next].name<<")";
                    next=path[over][next];
                }
                cout<<"-->"<<v[over].num<<"("<<v[over].name<<")";
                
            }
            cout<<endl;
            cout<<v[begin].num<<"到"<<v[over].num<<"距离为："<<a[begin][over]<<endl;
            break;
        }
            
		case '2':
        {
			cout<<"请输入起点：";
			cin>>starts;
			cout<<"请输入终点：";
			cin>>ends;
			for(int i=1;i<=n;i++)
				if(starts==v[i].name)
					begin=i;
            for(int i=1;i<=n;i++)
                if(ends==v[i].name)
                    over=i;
            if(begin==0||over==0)
            {
                cout<<"\t\t做不到！对不起！"<<endl;
               
                break;
            }
            if(begin!=over)
            {
                cout<<v[begin].name<<"("<<v[begin].num<<")";
                int next=path[over][begin];
                while(next !=over)
                {
                    cout<<"-->"<<v[next].name<<"("<<v[next].num<<")";
                    next=path[over][next];
                }
                cout<<"-->"<<v[over].name<<"("<<v[over].num<<")";
                
            }
            cout<<endl;
            cout<<v[begin].name<<"("<<v[begin].num<<")"<<"到"<<v[over].name<<"("<<v[over].num<<")"<<"距离为："<<a[begin][over]<<endl;
            break;
        }
    }
}

//介绍查看
void graph::show()
{
    char choose;
    cout<<"请输入您想了解的景点代号"<<endl;
    cin>>choose;
    switch(choose)
    {
		case'A':{
            cout<<"一柱擎天，代号A，序号1"<<endl;break;}
	    case'B':{
			cout<<"二龙戏珠，代号B，序号2"<<endl;break;}
		case'C':{
			cout<<"三顾茅庐，代号C，序号3"<<endl;break;}
		case'D':{
			cout<<"四面楚歌，代号D，序号4"<<endl;break;}
		case'E':{
			cout<<"五福临门，代号E，序号5"<<endl;break;}
		case'F':{
			cout<<"六月飞霜，代号F，序号6"<<endl;break;}
		case'G':{
			cout<<"七行俱下，代号G，序号7"<<endl;break;}
		case'H':{
			cout<<"八音迭奏，代号H,序号8"<<endl;break;}
		case'I':{
			cout<<"九九归一，代号I，序号9"<<endl;break;}
		case'J':{
			cout<<"十面埋伏，代号J，序号10"<<endl;break;}
		case'K':{
			cout<<"百川归海，代号K，序号11"<<endl;break;}
		case'L':{
			cout<<"千山万壑，代号L，序号12"<<endl;break;}
	    case'M':{
			cout<<"万家灯火，代号M，序号13"<<endl;break;}
		default:{
			cout<<"未找到！";
			break;}
    }
}




//...............................
int main()
{
	char choose;
	cout<<endl;
	cout<<"**********************************"<<endl;
	cout<<"        公园导航系统           "<<endl;
	cout<<"1.景点代号查询                     "<<endl;
	cout<<"2.查询从一点到各个景点的最短路径"<<endl;
	cout<<"3.查看参观路线最短路径         "<<endl;
	cout<<"4.查询景点信息                 "<<endl;
	cout<<"5.退出                         "<<endl;
	cout<<"**********************************"<<endl;
	cout<<"请输入：";
	cin>>choose;
	graph school;
	switch(choose)
	{
        case '1':
		{
            school.print();
            main();
            break;
		}
        case '2':
		{
            school.all();
            main();
            break;
		}
        case '3':
		{
            school.search();
            main();
            break;
		}
        case '4':
		{
            school.show();
            main();
            break;
		}
        case '5':
		{
            cout<<"再见！";
            break;
		}
        default:
		{
			cout<<"对不起，您输入错误！";
			main();
			break;
		}
	}
    return 0;
    
}