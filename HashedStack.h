#ifndef HASHEDSTACK_H_
#define HASHEDSTACK_H_
#include <map>

using namespace std;

class Node{
public:
	Node* next;
	Node* prev;
	char payload;
	int time;

	Node(Node* prev, Node* next, char payload) {
		this->prev=prev;
		this->next=next;
		this->payload=payload;
		this->time = 0;
	}
};

class HashedStack{
private:
    map<char, Node*>* basemap;
    Node* first;
    Node* last;

public:
	HashedStack(const char* letters, int length, int initial);
	void moveToTop(char letter, int time);
	char getBottom();
	char getSecondFromBottom();
	int getBottomTime();
	int getSecondFromBottomTime();
	~HashedStack();
};

#endif
