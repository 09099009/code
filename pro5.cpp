#include<cstdio>
#include<iostream>
#include<stack>
using namespace std;

class Solution{
public:
	void push(int node){
		stack1.push(node);	
	}
	int pop(){
		int top;
		while(!stack1.empty()){
			int node = stack1.top();
			stack2.push(node);
			stack1.pop();
		}
		if(!stack2.empty()){
			top = stack2.top();
			stack2.pop();
		}
		while(!stack2.empty()){
			int node = stack2.top();
			stack1.push(node);
			stack2.pop();
		}

		return top;
	}
private:
	stack<int> stack1;
	stack<int> stack2;
};

int main(){
	Solution *s = new Solution();
	s->push(1);
	s->push(2);
	s->push(3);
	cout << s->pop() << s->pop() << s->pop() << endl;
}

