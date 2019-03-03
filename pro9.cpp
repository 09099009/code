#include<cstdio>
#include<iostream>
using namespace std;

struct ListNode{
	int val;
	struct ListNode *next;
};

class Solution{
public:
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k){
		if(k == 0){
			return NULL;
		}
		ListNode *p1, *p2 = pListHead;
		for(int i = 1; i < k; ++i){
			if(p2 != NULL){
				p2 = p2->next;
			}
		}
		if(p2 == NULL){
			return NULL;
		}
		p1 = pListHead;
		p2 = p2->next;
		while(p2 != NULL){
			p1 = p1->next;
			p2 = p2->next;
		}
		return p1;
	}
};

int main(){
	ListNode *p1 = new ListNode();
	p1->val = 1;

	ListNode *p2 = new ListNode();
	ListNode *p3 = new ListNode();
	ListNode *p4 = new ListNode();
	ListNode *p5 = new ListNode();
	p2->val = 2;
	p3->val = 3;
	p4->val = 4;
	p5->val = 5;
	p1->next = p2;
	p2->next = p3;
	p3->next = p4;
	p4->next = p5;
	Solution *s = new Solution();
	cout << s->FindKthToTail(p1, 2)->val << endl;
}

