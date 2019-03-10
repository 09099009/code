#include<cstdlib>

struct AvlNode{
	int data;
	int height;
	AvlNode *left;
	AvlNode *right;
	AvlNode(const int d): data(d), left(NULL), right(NULL), height(0){}
};

class AvlTree{
public:
	AvlTree(){}
	~AvlTree(){}
	AvlNode *root;
	AvlNode *FindMax(AvlNode *t);
	AvlNode *FindMin(AvlNode *t);
	void Insert(AvlNode *&t, int x);
	bool Delete(AvlNode *&t, int x);
	void Inorder(AvlNode *t);
	void Preorder(AvlNode *t);
private:
	int GetHeight(AvlNode *t);
	AvlNode *LL(AvlNode *t);
	AvlNode *LR(AvlNode *t);
	AvlNode *RR(AvlNode *t);
	AvlNode *RL(AvlNode *t);
};

