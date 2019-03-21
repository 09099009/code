#include<cstdlib>

struct Point{
	int x;
	int y;
	Point(const int _x, const int _y): x(_x), y(_y){}
};

struct AvlNode{
	Point data;
	int height;
	AvlNode *left;
	AvlNode *right;
	AvlNode(const Point p): data(p), left(NULL), right(NULL), height(0){}
};

class AvlTree{
public:
	AvlTree(){}
	~AvlTree(){}
	AvlNode *root;
	AvlNode *FindMax(AvlNode *t);
	AvlNode *FindMin(AvlNode *t);
	void Insert(AvlNode *&t, Point p);
	bool Delete(AvlNode *&t, Point p);
	void Inorder(AvlNode *t);
	void Preorder(AvlNode *t);
private:
	int GetHeight(AvlNode *t);
	AvlNode *LL(AvlNode *t);
	AvlNode *LR(AvlNode *t);
	AvlNode *RR(AvlNode *t);
	AvlNode *RL(AvlNode *t);
};

