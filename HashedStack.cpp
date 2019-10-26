#include "HashedStack.h"
#include <map>
#include <iostream>

using namespace std;

HashedStack::HashedStack(const char* letters, int length) {
	if(length < 2){
		throw 1;
	}

	basemap = new map<char, Node*>();

	first = new Node(0,0,letters[0]);
	last = first;
	basemap->operator[] (letters[0])=first;

	for(int i = 1; i < length; i++) {
		Node* newEnd = new Node(last, 0, letters[i]);
		basemap->operator[] (letters[i])=newEnd;
		last->next = newEnd;
		last = newEnd;
	}

}

void HashedStack::moveToTop(char letter, int time) {
	Node* move = basemap->operator[] (letter);
	move->time = time;

	if(move == first)
		return;
	else if (move == last)
	{
		last = move->prev;
		last->next = 0;
		move->prev = 0;
		move->next = first;
		first->prev = move;
		first = move;
	}
	else
	{
		move->prev->next = move->next;
		move->next->prev = move->prev;
		move->prev = 0;
		move->next = first;
		first->prev = move;
		first = move;
	}
}

char HashedStack::getBottom() {
	return last->payload;
}

char HashedStack::getSecondFromBottom() {
	return last->prev->payload;
}

int HashedStack::getBottomTime() {
	return last->time;
}

int HashedStack::getSecondFromBottomTime() {
	return last->prev->time;
}

HashedStack::~HashedStack(){
	Node* iter = first;

	while(iter!=0){
		Node* temp = iter->next;
		delete iter;
		iter = temp;
	}

	delete basemap;
}
