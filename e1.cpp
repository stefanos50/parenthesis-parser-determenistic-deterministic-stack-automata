#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
struct Node{
	char data;
	Node *next;
};
class Stack{
	public:
		Stack();
		~Stack();
		void push(char a);
		char pop();	
		string toString();
		bool isEmpty();
		char GetTop();
	private:
		Node *top;
};
Stack::Stack(){
	top = NULL;
}
Stack::~Stack(){
	while(!isEmpty())
		pop();
}
void Stack::push(char d){ //Add a character to the top of the stack
	Node *temp = new Node;
	temp->data = d;
	temp->next = top;
	top = temp;
}
char Stack::pop(){ //Delete the element at the top of the stack if stuck is not empty
	if(!isEmpty()){
		char value = top->data;
		Node *oldtop = top;
		top = oldtop -> next;
		delete oldtop;
		return value;
	}else{
		return 'n';
	}
}
string Stack::toString(){//Print stack elements
	string result = "";
	if(isEmpty()){
		result = result + "$";
	}else{
		Node *current = top;
		while(current !=NULL){
			result = result + current->data;
			current = current ->next;
		}
		result = result +"$";
		reverse(result.begin(), result.end()); 
		return result;
	}
}
bool Stack::isEmpty(){ //Check if stack is empty
	return(top==NULL);
}
char Stack::GetTop(){ //Return the element that is at the top of the stack
	char val;
	Node *current = top;
	if(isEmpty()){
		return '$';
	}
	val = current->data;
	return val;
}
string ShowInput(int l,string str){ //Show the input
	string input = "";
	int s = 0;
	for(char& c : str) {
		if(c=='('||c==')'){
			if(l <= s){
				input += c;
			}
			s++;
		}
	}
	return input;
}
void doesFileExist(char* filename){ //Check if the file name given as argument exists
	FILE *file;
	if(file = fopen(filename,"r")){
		fclose(file);
		return;
	}
	cout<<"File does not exists"<<endl;
	exit(1);
	
}
int main(int argc, char* argv[]){
		ifstream inFile;
		if(argc == 2){ //Check if arguments are given correct
			doesFileExist(argv[1]);
			inFile.open(argv[1]);
		}else{
			cout<<"more or less arguments given"<<endl;	
			exit(1);
		}
		int numLines = 0;
		ifstream in(argv[1]);
		string unused;
		while ( std::getline(in, unused) ){ 
			if(!unused.empty()) 
				++numLines;
		}
		int i=0;
		cout<<"The file have number of non empty lines: "<<numLines<<endl;
		string lines[numLines];
		string un;
		in.clear();
		in.seekg(0, ios::beg);
		string alllines="";
		while ( std::getline(in, un) ){ 
			if(!un.empty()){ 
				alllines += un;
			}
		}
		i = 0;
		char a;
		bool flag=true,foundparenth=false,show=true,haveerror=false,linevalid=true,nullstackandleftpar=false,errorfound=false;
		Stack *s = new Stack();//stack initialization
		string state = "k1";
		int length = -1;
		cout<<"All the parenthesis found in file:"<<ShowInput(0,alllines)<<endl;
		while (inFile.get(a))
		{
				if((a=='(' || a==')') && nullstackandleftpar==false){ //Read only the parenthesis and avoid reading anything else that the file contains
					length++;
					cout<<"Stack: "<<s->toString()<<"   "<<"State: "<<state<<"   "<<"Input: "<<ShowInput(length,alllines)<<endl;
					foundparenth = true;
					if(s->GetTop()=='A' && a == '('){ //Check with if based of DAS rules
						cout<<"Using p(k1,A,'(')=(k1,AA)..."<<endl;
						s->push('A');
					}
					else if(s->GetTop()=='$' && a=='('){
						cout<<"Using p(k1,$,'(')=(k1,$A)..."<<endl;
						s->push('A');
					}
					else if(s->GetTop()=='A' && a==')'){
						cout<<"Using p(k1,A,')')=(k1,empty)..."<<endl;
						s->pop();
					}else if(s->GetTop()=='$' && a==')'){
						nullstackandleftpar = true;
						continue;
					}
				}
		}
	
				if(foundparenth){ //If parenthesis existed in the file
					if(nullstackandleftpar){ 
						errorfound=true;
						cout<<"Not such a rule found for $ stack and input )"<<endl;
						cout<<"NO"<<endl;
					}else{
						cout<<"Stack: "<<s->toString()<<"   "<<"State: "<<state<<"   "<<"Input: empty"<<endl; //Είσοδος το κενό
						if(s->GetTop()=='$'){
							cout<<"Using p(k1,$,empty)=(k2,empty)..."<<endl;
							state="k2";
						}else if(s->GetTop()=='A'){
							state = "k1";
						}
						if(state=="k1"){ //Based on the final state answear YES ή NO. State k1 = NO , state k2 = YES
							errorfound=true;
							cout<<"NO"<<endl;
						}else if(state=="k2"){
							cout<<"Stack: "<<s->toString()<<"   "<<"State: "<<state<<"   "<<"Input: empty"<<endl;
							cout<<"YES"<<endl;
						}
					}
				}else{ //If no parenthesis existed in the file then the file is balanced so print YES
					cout<<"YES"<<endl;
				}
return 0;
}