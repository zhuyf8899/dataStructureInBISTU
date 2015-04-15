// LNode.cpp : Defines the entry point for the console application.
//

#include "iostream"
using namespace std;

struct Node{
	int data;
	Node *next;
};

class LNode{
public:
	int length;
	Node *head;

	LNode(){
		head = (Node*)malloc(sizeof(Node));
		head -> next = NULL;
		length++;
	}

	void insertelem(int i,int e){
		Node *p = head;
		Node *n ;
		if (i == 1){
			n = (Node*)malloc(sizeof(Node));
			n -> next = p;
			head = n;
			head ->data = e;
			length++;
		}
		else{
			for(int j = 0; j < i-2; j++){
				p = p -> next;
			}
			n = p -> next;
			p -> next = (Node*)malloc(sizeof(Node));
			p -> next -> data = e;
			p -> next -> next = n;
			length++;
		}
	}

	void showlist(){
		Node *p = head;
		for (int i = 0; i < length; i++){
			cout << p ->data << ' ';
			p = p -> next;
		}
			cout << endl;
		
	}
	
	void deleteelem(int i){
		Node *p = head;
		Node *n;
		n = p -> next;
		if (i == 1){
			head = n;
			free(p);
			length--;
		}
		else{
			for(int j = 0; j < i-2; j++){
				p = p -> next;
			}
			p -> next = n -> next;
			free(n);
			length--;
		}

	}
		
	int searchelem(int i){
		Node *p = head;
		
		for(int j = 0; j < length; j++){
			if(p -> data == i){
				return true;
			}

			p = p -> next;
		}
		
		return false;
	}
};


int main()
{
	LNode a;
	a.head -> data = 1;
	a.length = 1;
	for (int i = 2; i < 10; i++){
		a.insertelem(i,i);
	}
	a.showlist();
	a.insertelem(2,99);
	a.showlist();
	a.deleteelem(1);
	a.showlist();
	cout << a.searchelem(8) << endl;
	cout << a.searchelem(20) << endl;
	return 0;
}

