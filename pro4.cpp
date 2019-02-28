#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

struct TreeNode{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

class Solution{
public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin){
		if(pre.size() == 0){
			return NULL;
		}
		TreeNode *tn = new TreeNode();
		tn->val = *pre.begin();
		int k = find(vin, *pre.begin());
		vector<int> l_pre(pre.begin() + 1, pre.begin() + 1 + k);
		vector<int> r_pre(pre.begin() + 1 + k, pre.end());
		vector<int> l_vin(vin.begin(), vin.begin() + k);
		vector<int> r_vin(vin.begin() + k + 1, vin.end());
		tn->left = reConstructBinaryTree(l_pre, l_vin);
		tn->right = reConstructBinaryTree(r_pre, r_vin);
		return tn;
	}
	void pre(TreeNode *p){
		if(p == NULL){
			return;
		}
		cout << p->val << " ";
		pre(p->left);
		pre(p->right);
	}
private:
	int find(vector<int> arr, int key){
		for(int i = 0; i < arr.size(); ++i){
			if(arr[i] == key){
				return i;
			}
		}
	}
};

int main(){
	vector<int> pre;
	vector<int> vin;
	int p[8] = {1, 2, 4, 7, 3, 5, 6, 8};
	int v[8] = {4, 7, 2, 1, 5, 3, 8, 6};
	for(int i = 0; i < 8; ++i){
		pre.push_back(p[i]);
		vin.push_back(v[i]);
	}
	Solution *s = new Solution();
	TreeNode *tn = s->reConstructBinaryTree(pre, vin);
	s->pre(tn);
	cout << endl;
}

