#ifndef trieNode
#define trieNode
#include <iostream>
using namespace std;

class Node{
	char data;
	bool isWord;
	Node *left, *right, *equal;

public:

	Node(): left(NULL), right(NULL), equal(NULL), data('\0'), isWord(false){}
	Node(char c): left(NULL), right(NULL), equal(NULL), data(c), isWord(false){}

	~Node(){
		if(this!= NULL){
			if(this->left!= NULL){
				delete this-> left;
			}
			if(this->right!= NULL){
				delete this-> right;
			}
			if(this->equal!= NULL){
				delete this->equal;
			}	
		}
		
	}

	friend class trnSearch;

};














#endif