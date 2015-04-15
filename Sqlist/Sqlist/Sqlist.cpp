// Sqlist.cpp : Defines the entry point for the console application.
//
#define LIST_INIT_SIZE 100                                //初始分配量
#define LISTINCREMENT 10                                  //增量
#include "iostream"
//#include "cstdlib"
using namespace std;                                      //初始化顺序表
class Sqlist{
public:
	int length;
	int listsize;
	int* elem;
	Sqlist() {
		length = 0;
		listsize = LIST_INIT_SIZE;
		elem =(int*) malloc (sizeof(int)*LIST_INIT_SIZE);
	if (!elem) exit(OVERFLOW);
	}

	void insertelem(int i,int e){                         //插入一个元素
		if (length+1 < listsize){
			int j;
			for( j = length; j+2 > i ;j--){
				elem[j+1] = elem[j];
			}
			elem[j+1] = e;
			length++;
		}

	}

	void showlist(){                                       //show函数
		for(int i = 0; i < length; i++ )
			cout << elem[i] << ' ';
			cout << endl;
	}

	void deleteelem(int i){                                //删除一个元素
		for(int j = i-1;j <= length; j++ ){
			elem[j] = elem[j+1];
		}
		length--;
	}
	
	int searchelem(int x){                                 //查找一个元素
		for(int i = 0; i < length; i++ ){
			if (elem[i] == x)
			{
				return true;
			}
		}
		return false;
	}
};

int main()
{
	Sqlist s;
	for (int i = 0; i < 10; i++){
		s.elem[i] = i;
	}
	s.length = 10;
	s.showlist();
	s.insertelem(3,5);
	s.showlist();
	s.deleteelem(3);
	s.showlist();
	cout<<s.searchelem(6)<<endl;
	cout<<s.searchelem(11)<<endl;
	return 0;
}

