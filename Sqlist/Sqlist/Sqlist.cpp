// Sqlist.cpp : Defines the entry point for the console application.
//
#define LIST_INIT_SIZE 100                                //��ʼ������
#define LISTINCREMENT 10                                  //����
#include "iostream"
//#include "cstdlib"
using namespace std;                                      //��ʼ��˳���
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

	void insertelem(int i,int e){                         //����һ��Ԫ��
		if (length+1 < listsize){
			int j;
			for( j = length; j+2 > i ;j--){
				elem[j+1] = elem[j];
			}
			elem[j+1] = e;
			length++;
		}

	}

	void showlist(){                                       //show����
		for(int i = 0; i < length; i++ )
			cout << elem[i] << ' ';
			cout << endl;
	}

	void deleteelem(int i){                                //ɾ��һ��Ԫ��
		for(int j = i-1;j <= length; j++ ){
			elem[j] = elem[j+1];
		}
		length--;
	}
	
	int searchelem(int x){                                 //����һ��Ԫ��
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

