#include<iostream>
#include<limits>
#include<cstdlib>
using namespace std;

struct Point{
	int64_t x;
	int64_t y;
	Point(const int64_t _x, const int64_t _y): x(_x), y(_y){}
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
	AvlNode *FindMax(AvlNode *t){
		if(t == NULL){
			return NULL;
		}
		if(t->right == NULL){
			return t;
		}
		return FindMax(t->right);
	}
	AvlNode *FindMin(AvlNode *t){
		if(t == NULL){
			return NULL;
		}
		if(t->left == NULL){
			return t;
		}
		return FindMin(t->left);
	}
	void Insert(AvlNode *&t, Point p){
		if(t == NULL){
			t = new AvlNode(p);
		}
		else{
			if(p.x < t->data.x || p.x == t->data.x && p.y < t->data.y){
				Insert(t->left, p);
				if(GetHeight(t->left) - GetHeight(t->right) > 1){
					if(p.x < t->left->data.x || p.x == t->left->data.x && p.y < t->left->data.y){
						t = LL(t);
					}
					else if(p.x > t->left->data.x || p.x == t->left->data.x && p.y > t->left->data.y){
						t = LR(t);
					}
				}

			}
			else if(p.x > t->data.x || p.x == t->data.x && p.y > t->data.y){
				Insert(t->right, p);
				if(GetHeight(t->right) - GetHeight(t->left) > 1){
					if(p.x < t->right->data.x || p.x == t->right->data.x && p.y < t->right->data.y){
						t = RL(t);
					}
					else if(p.x > t->right->data.x || p.x == t->right->data.x && p.y > t->right->data.y){
						t = RR(t);
					}
				}
			}
			t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
		}
	}
	bool Delete(AvlNode *&t, Point p){
		if(t == NULL){
			return false;
		}
		if(p.x == t->data.x && p.y == t->data.y){
			if(t->left != NULL && t->right != NULL){
				if(GetHeight(t->left) > GetHeight(t->right)){
					t->data = FindMax(t->left)->data;
					Delete(t->left, t->data);
				}
				else{
					t->data = FindMin(t->right)->data;
					Delete(t->right, t->data);
				}
				t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
			}
			else{
				AvlNode *old = t;
				t = (t->left != NULL) ? t->left : t->right;
				delete old;
			}
		}
		else{
			if(p.x < t->data.x || p.x == t->data.x && p.y < t->data.y){
				Delete(t->left, p);
				if(GetHeight(t->right) - GetHeight(t->left) > 1){
					if(GetHeight(t->right->left) > GetHeight(t->right->right)){
						t = RL(t);
					}
					else{
						t = RR(t);
					}
				}
				else{
					t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
				}
			}
			else if(p.x > t->data.x || p.x == t->data.x && p.y > t->data.y){
				Delete(t->right, p);
				if(GetHeight(t->left) - GetHeight(t->right) > 1){
					if(GetHeight(t->left->left) > GetHeight(t->left->right)){
						t = LL(t);
					}
					else{
						t = LR(t);
					}
				}
				else{
					t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
				}
			}
		}
	}
private:
	int GetHeight(AvlNode *t){
		if(t == NULL){
			return -1;
		}
		else{
			return t->height;
		}
	}
	AvlNode *LL(AvlNode *t){
		AvlNode *p = t->left;
		t->left = p->right;
		p->right = t;
		t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
		p->height = max(GetHeight(p->left), GetHeight(p->right)) + 1;

		return p;
	}
	AvlNode *LR(AvlNode *t){
		AvlNode *p = RR(t->left);
		t->left = p;
		return LL(t);
	}
	AvlNode *RR(AvlNode *t){
		AvlNode *p = t->right;
		t->right = p->left;
		p->left = t;
		t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
		p->height = max(GetHeight(p->left), GetHeight(p->right)) + 1;

		return p;
	}
	AvlNode *RL(AvlNode *t){
		AvlNode *p = LL(t->right);
		t->right = p;
		return RR(t);
	}
};

bool toLeft(const Point &p1, const Point &p2, const Point &p3){
	int64_t res = p1.x * p2.y - p1.y * p2.x + p2.x * p3.y - p2.y * p3.x + p3.x * p1.y - p3.y * p1.x;
  	return res > 0;
}

bool toRight(const Point &p1, const Point &p2, const Point &p3){
	int64_t res = p1.x * p2.y - p1.y * p2.x + p2.x * p3.y - p2.y * p3.x + p3.x * p1.y - p3.y * p1.x;
	return res < 0;
}

Point FindNext(const AvlNode *t, const Point &p, bool distinct){
	Point tmp(numeric_limits<int64_t>::max(), numeric_limits<int64_t>::max());
	while(t != NULL){
		if(p.x < t->data.x){
			if(t->data.x < tmp.x || t->data.x == tmp.x && t->data.y < tmp.y){
				tmp = t->data;
			}
			t = t->left;	
		}
		else if(p.x > t->data.x){
			t = t->right;
		}
		else{
			if(distinct){
				if(p.y < t->data.y){
					if(tmp.x != t->data.x){
						tmp = t->data;
					}
					else{
						if(t->data.y < tmp.y){
							tmp = t->data;
						}
					}
					t = t->left;
				}
				else{
					t = t->right;
				}
			}
			else{
				if(p.y <= t->data.y){
					if(tmp.x != t->data.x){
						tmp = t->data;
					}
					else{
						if(t->data.y < tmp.y){
							tmp = t->data;
						}
					}
					t = t->left;
				}
				else{
					t = t->right;
				}
			}
		}
	}
	return tmp;
}

Point FindLast(const AvlNode *t, const Point &p, bool distinct){
	Point tmp(numeric_limits<int64_t>::min(), numeric_limits<int64_t>::min());
	while(t != NULL){
		if(p.x > t->data.x){
			if(t->data.x > tmp.x || t->data.x == tmp.x && t->data.y > tmp.y){
				tmp = t->data;
			}
			t = t->right;
		}
		else if(p.x < t->data.x){
			t = t->left;
		}
		else{
			if(distinct){
				if(p.y > t->data.y){
					if(tmp.x != t->data.x){
						tmp = t->data;
					}
					else{
						if(t->data.y > tmp.y){
							tmp = t->data;
						}
					}
					t = t->right;
				}
				else{
					t = t->left;
				}
			}
			else{
				if(p.y >= t->data.y){
					if(tmp.x != t->data.x){
						tmp = t->data;
					}
					else{
						if(t->data.y > tmp.y){
							tmp = t->data;
						}
					}
					t = t->right;
				}
				else{
					t = t->left;
				}
			}
		}
	}
	return tmp;
}

void LTR_Upper(AvlTree *t, const Point &p){
	Point p1 = FindNext(t->root, p, true);
	if(p1.x == numeric_limits<int64_t>::max()){
		return;
	}
	Point p2 = FindNext(t->root, p1, true);
	while(p2.x != numeric_limits<int64_t>::max()){
		if(!toRight(p, p1, p2)){
			t->Delete(t->root, p1);
			p1 = p2;
			p2 = FindNext(t->root, p1, true);
		}
		else{
			break;
		}
	}
}

void RTL_Upper(AvlTree *t, const Point &p){
	Point p1 = FindLast(t->root, p, true);
	if(p1.x == numeric_limits<int64_t>::min()){
		return;
	}
	Point p2 = FindLast(t->root, p1, true);
	while(p2.x != numeric_limits<int64_t>::min()){
		if(!toRight(p2, p1, p)){
			t->Delete(t->root, p1);
			p1 = p2;
			p2 = FindLast(t->root, p1, true);
		}
		else{
			break;
		}
	}
}

void LTR_Lower(AvlTree *t, const Point &p){
	Point p1 = FindNext(t->root, p, true);
	if(p1.x == numeric_limits<int64_t>::max()){
		return;
	}
	Point p2 = FindNext(t->root, p1, true);
	while(p2.x != numeric_limits<int64_t>::max()){
		if(!toRight(p2, p1, p)){
			t->Delete(t->root, p1);
			p1 = p2;
			p2 = FindNext(t->root, p1, true);
		}
		else{
			break;
		}
	}
}

void RTL_Lower(AvlTree *t, const Point &p){
	Point p1 = FindLast(t->root, p, true);
	if(p1.x == numeric_limits<int64_t>::min()){
		return;
	}
	Point p2 = FindLast(t->root, p1, true);
	while(p2.x != numeric_limits<int64_t>::min()){
		if(!toRight(p, p1, p2)){
			t->Delete(t->root, p1);
			p1 = p2;
			p2 = FindLast(t->root, p1, true);
		}
		else{
			break;
		}
	}
}

bool InUpperConv(const Point &p, const AvlTree *upperConv){
	Point p1 = FindLast(upperConv->root, p, false);
	if(p1.x == p.x && p1.y == p.y){
		return true;
	}
	Point p2 = FindNext(upperConv->root, p, false);
	if(p2.x == p.x && p2.y == p.y){
		return true;
	}
	if(p1.x == numeric_limits<int64_t>::min() || p2.x == numeric_limits<int64_t>::max()){
		return false;
	}
	if(toLeft(p1, p2, p)){
		return false;
	}
	return true;
}

bool InLowerConv(const Point &p, const AvlTree *lowerConv){
	Point p1 = FindLast(lowerConv->root, p, false);
	if(p1.x == p.x && p1.y == p.y){
		return true;
	}
	Point p2 = FindNext(lowerConv->root, p, false);
	if(p2.x == p.x && p2.y == p.y){
		return true;
	}
	if(p1.x == numeric_limits<int64_t>::min() || p2.x == numeric_limits<int64_t>::max()){
		return false;
	}
	if(toLeft(p2, p1, p)){
		return false;
	}
	return true;
}

void UpdateAvl(const Point &p,  AvlTree *&upperConv, AvlTree *&lowerConv){
	if(!InUpperConv(p, upperConv)){
		LTR_Upper(upperConv, p);
		RTL_Upper(upperConv, p);
		upperConv->Insert(upperConv->root, p);
	}
	if(!InLowerConv(p, lowerConv)){
		LTR_Lower(lowerConv, p);
		RTL_Lower(lowerConv, p);
		lowerConv->Insert(lowerConv->root, p);
	}
}

int main(){
	ios::sync_with_stdio(false);	
	AvlTree *upperConv = new AvlTree();
	AvlTree *lowerConv = new AvlTree();
	int n, operation;
	Point p(0, 0);
	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> operation >> p.x >> p.y;
		if(operation == 1){
			UpdateAvl(p, upperConv, lowerConv);
		}
		else if(operation == 2){
			if(!InUpperConv(p, upperConv) || !InLowerConv(p, lowerConv)){
				cout << "NO" << endl;
			}
			else{
				cout << "YES" << endl;
			}
		}
		else{
		
		}
	}
}

