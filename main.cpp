#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <unordered_set>
#include "HashedStack.h"

using namespace std;

//Co-occurrence algorithm 3
void getCoocurrence(const char* trace, const char* set){
	unordered_set<char> charSet;
	int trace_len = strlen(trace);

	for(int i = 0; i < strlen(set); i++){
		charSet.insert(set[i]);
	}

	HashedStack stack(set, strlen(set), 0);
	map<int,int> histogram;

	for(int i = 0; i < trace_len; i++){
		char cur = trace[i];

		if(charSet.find(cur) != charSet.end()){
			if(stack.getBottom() == cur){
				histogram[i-stack.getBottomTime()]++;
				histogram[i-stack.getSecondFromBottomTime()]--;
			}

			stack.moveToTop(cur, i+1);
		}
	}

	histogram[trace_len-stack.getBottomTime()]++;

	int count_1 = 0;
	int count_2 = 0;

	for (int i = trace_len; i>= 1; i--) {
		int num = (histogram.find(i) == histogram.end()) ? 0:histogram[i];
		count_1+=num;
		count_2+=num*(i+1);

		if(i<=20)
			cout<<i<<"-"<<(trace_len-i+1)-(count_2-i*count_1)<<endl;
	}
}

//Co-occurrence algorithm 1
void getCoocurrenceSingleLength(const char* trace, const char* set){
	unordered_set<char> charSet;
	int trace_len = strlen(trace);
	
	for(int length = 20; length>0; length--){

	int count = 0;

	for(int i = 0; i < strlen(set); i++){
		charSet.insert(set[i]);
	}

	HashedStack stack(set, strlen(set), -2*trace_len);
	map<int,int> histogram;

	for(int i = 0; i < trace_len; i++){
		char cur = trace[i];

		if(charSet.find(cur) != charSet.end()){
			stack.moveToTop(cur, i);
		}

		int max_tesla = i-stack.getBottomTime();

		if(max_tesla<length){
			count++;
		}
	}

	cout<<length<<"-"<<count<<endl;
	}
}

int main() {
	std::ifstream in("words.txt");

	if (in) {
	    in.seekg(0, std::ios::end);
	    size_t len = in.tellg();
	    in.seekg(0);
	    std::string contents(len + 1, '\0');
	    in.read(&contents[0], len);
	    getCoocurrence(contents.c_str(), "ABC");
	    getCoocurrenceSingleLength(contents.c_str(), "ABC");
	}
}
