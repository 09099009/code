#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct ListNode{
	int val;
	struct ListNode *next;
};

class Solution{
public:
	vector<int> printListFromTailToHead(ListNode *head){
		ListNode *p = head;
		vector<int> l;
		while(p != NULL){
			l.push_back(p->val);
			p = p->next;
		}
		reverse(l.begin(), l.end());
		return l;
	}
};

int main(){
	ListNode *p = new ListNode();
	p->val = 1;
	ListNode *q = new ListNode();
	q->val = 2;
	ListNode *r = new ListNode();
	r->val = 3;
	p->next = q;
	q->next = r;
	r->next = NULL;
	vector<int> l;
	Solution *s = new Solution();
	l = s->printListFromTailToHead(p);
	for(vector<int>::iterator i = l.begin(); i != l.end(); ++i){
		cout << *i << endl;
	}
}

