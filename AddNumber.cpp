#include<iostream>
#include<cstdio>
using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(NULL){}
};

class Solution{
public:
	ListNode* addTwoNumbers(ListNode *l1, ListNode *l2){
		ListNode *l = new ListNode(0), *p = l;
		int out = 0, x, y, sum;
		while(l1 != NULL || l2 != NULL){
			x = (l1 == NULL) ? 0 : l1->val;
			y = (l2 == NULL) ? 0 : l2->val;
			sum = x + y + out;
			p->next = new ListNode(0);
			p = p->next;
			p->val = sum % 10;
			out = sum / 10;
			l1 = (l1 == NULL) ? NULL : l1->next;
			l2 = (l2 == NULL) ? NULL : l2->next;
		}
		if(out != 0){
			p->next = new ListNode(1);
		}
		return l->next;
	}
};

int main(){
	ListNode *p = new ListNode(9), *q = new ListNode(1);
	ListNode *p_move = p;
	p_move->next = new ListNode(9);
	p_move = p_move->next;
	p_move->next = new ListNode(9);
	Solution s;
	ListNode *r;
	r = s.addTwoNumbers(p, q);
	while(r != NULL){
		cout << r->val << " ";
		r = r->next;
	}
	cout << endl;
}

