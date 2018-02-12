#include <iostream>
#include <vector>
#include <string>
#include "trieNode.h"
using namespace std;

class trnSearch{
	Node *root;
	int totalWords;

public:

	trnSearch(): root(NULL), totalWords(0){}

	~trnSearch(){
		delete root;
	}

	void insert(string);
	void insertHelper(string, int, Node*&);
	void printAll();
	void printAllHelper(Node*&, vector<char>);
	void search(string);
	bool searchHelper(string, int i, Node *&root, vector<char>);
	void searchByFrag(string);
	void searchByFragHelper(string, Node *&root);
};

void trnSearch:: printAllHelper(Node *&root, vector<char> word){
	if(root==NULL){
		return;
	}
	word.push_back(root-> data);

	if(root-> isWord){
		word.push_back('\0');
		for(int i=0; i< word.size(); i++){
			cout<< word[i];
		}
		cout<< endl;
		word.pop_back();
	}

	printAllHelper(root-> equal, word);	//this will print the  word  which has its previous character == so far traversed tree
	word.pop_back();  //popped coz we will traverse left and right of current node(which is not the part of word that will be formed by left and right child of current node)

	printAllHelper(root-> left, word);
	printAllHelper(root-> right, word);

	

}

void trnSearch:: printAll(){
	vector<char> word;
	printAllHelper(root, word);

	cout<< "Total number of words in tree are- "<< this-> totalWords<< endl;
}

void trnSearch:: insertHelper(string word, int i, Node *&root){
	if(root== NULL){
		root= (word[i]!= '\0')? new Node(word[i]): NULL;
		if(word[i+1]== '\0'){				//means word[i] is last character;
			root-> isWord= true;			//word is completed;
			this-> totalWords++;
			return;
		}
		insertHelper(word, i+1, root-> equal);
		
	}

	else if((i+ 1)== word.size()){
		if(root-> isWord && root->data== word[i]){
			cout<< word<< " is already present"<< endl;
		}
		else{
			root-> isWord= true;
			this-> totalWords++;	
		}

		return;
	}

	else{
		if(word[i]< root-> data){
			insertHelper(word, i, root-> left);
		}
		else if(word[i]> root-> data){
			insertHelper(word, i, root-> right);
		}
		//this else if will be called if the word we are inserting is same as some existing word till value of i;
		else if(word[i]== root-> data){
			insertHelper(word, i+1, root-> equal);
		}
	}

}

void trnSearch:: insert(string word){
	insertHelper(word, 0, root);
}

bool trnSearch::searchHelper(string word, int i, Node *&root, vector<char> wordprint){
	if(root== NULL && i==0){
		cout<< "No such element present having "<< word<< " as common"<< endl;
		return false;
	}
	if(root== NULL ){
		cout<< "No such element present having "<< word<< " as common"<< endl;
		return false;
	}

	if(i== word.size()){
		// cout<< "returning true2"<< endl;
		return true;
	}

	if(root-> isWord && (i+1)== word.size()){//if encountered a complete word(in tree) and also searched word is also traversed completely
		if(root-> data== word[i]){
			wordprint.push_back(root->data);
			for(int i=0; i< wordprint.size(); i++){
				cout<< wordprint[i];
			}
			cout<< endl;
			// cout<< "returning false:"<<root->data<< endl;
			return true;
		}
		cout<< "No such element present having "<< word<< " as common"<< endl;
		return false;

			
	}

	if(root-> data== word[i]){
		wordprint.push_back(root->data);
		if(searchHelper(word, i+1, root-> equal, wordprint)){
			// cout<< "calling printAllHelperll"<< endl;
			printAllHelper(root->equal, wordprint);
			return false;
		}
	}
	else if(word[i]> root-> data){
		searchHelper(word, i, root-> right, wordprint);
	}

	else{
		searchHelper(word, i, root-> left, wordprint);
	}

	return false;
}

void trnSearch:: search(string word){
	vector<char> wordprint;
	searchHelper(word, 0, root, wordprint);
}

int main(){

	trnSearch tree;
	int choice;
	string word;
	bool loop;
	loop= true;

	while(loop){
	
		cout<< "1) Enter new Word"<< endl;
		cout<< "2) Print all words"<< endl;
		cout<< "3) Search a word"<< endl;
		cout<< "4) Exit"<< endl;

		cin>> choice;

		switch(choice){
			case 1: cout<< "Enter the word"<< endl;
					cin>> word;
					tree.insert(word);
					break;

			case 2: tree.printAll();	
					break;

			case 3: cout<< "Enter the word to be searched: ";
					cin>> word;
					tree.search(word);
					break;

			case 4: loop= false;
					break;		
		}

	}

	return 0;
}
