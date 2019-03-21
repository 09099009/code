#include<cstdlib>
#include<iostream>
#include<algorithm>
#include "AvlTree.h"
using namespace std;

int AvlTree::GetHeight(AvlNode *t){
	if(t == NULL){
		return -1;
	}
	else{
		return t->height;
	}
}

AvlNode *AvlTree::LL(AvlNode *t){
	AvlNode *p = t->left;
	t->left = p->right;
	p->right = t;
	t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
	p->height = max(GetHeight(p->left), GetHeight(p->right)) + 1;

	return p;
}

AvlNode *AvlTree::RR(AvlNode *t){
	AvlNode *p = t->right;
	t->right = p->left;
	p->left = t;
	t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
	p->height = max(GetHeight(p->left), GetHeight(p->right)) + 1;

	return p;
}

AvlNode *AvlTree::LR(AvlNode *t){
	AvlNode *p = RR(t->left);
	t->left = p;
	return LL(t);
}

AvlNode *AvlTree::RL(AvlNode *t){
	AvlNode *p = LL(t->right);
	t->right = p;
	return RR(t);
}

void AvlTree::Insert(AvlNode *&t, Point p){
	if(t == NULL){
		t = new AvlNode(p);
	}
	else{
		if(p.x < t->data.x){
			Insert(t->left, p);
			if(GetHeight(t->left) - GetHeight(t->right) > 1){
				if(p.x < t->left->data.x){
					t = LL(t);
				}
				else{
					t = LR(t);
				}
			}

		}
		else if(p.x > t->data.x){
			Insert(t->right, p);
			if(GetHeight(t->right) - GetHeight(t->left) > 1){
				if(p.x < t->right->data.x){
					t = RL(t);
				}
				else{
					t = RR(t);
				}
			}
		}
		else{
		
		}
		t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
	}
}

AvlNode *AvlTree::FindMax(AvlNode *t){
	if(t == NULL){
		return NULL;
	}
	if(t->right == NULL){
		return t;
	}
	return FindMax(t->right);
}

AvlNode *AvlTree::FindMin(AvlNode *t){
	if(t == NULL){
		return NULL;
	}
	if(t->left == NULL){
		return t;
	}
	return FindMin(t->left);
}

bool AvlTree::Delete(AvlNode *&t, Point p){
	if(t == NULL){
		return false;
	}
	if(p.x == t->data.x){
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
		if(p.x < t->data.x){
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
		else if(p.x > t->data.x){
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

void AvlTree::Preorder(AvlNode *t){
	if(t == NULL){
		return;
	}
	cout << t->data.x << "(" << t->height << ") ";
	Preorder(t->left);
	Preorder(t->right);
}

void AvlTree::Inorder(AvlNode *t){
	if(t == NULL){
		return;
	}
	Inorder(t->left);
	cout << t->data.x << "(" << t->height << ") ";
	Inorder(t->right);
}

/*int main(){
	AvlTree *tree = new AvlTree();
	int value;
	cout << "input number to construct AvlTree,(-1 to pause): " << endl;
	while(cin >> value){
		if(value == -1){
			break;
		}
		tree->Insert(tree->root, value);
	}
	cout << "inorder: " << endl;
	tree->Inorder(tree->root);
	cout << endl;
	cout << "preorder: " << endl;
	tree->Preorder(tree->root);
	cout << endl;
	while(cin >> value){
		cout << "input node to delete: ";
		tree->Delete(tree->root, value);
		cout << "inorder: " << endl;
		tree->Inorder(tree->root);
		cout << endl;
		cout << "preorder: " << endl;
		tree->Preorder(tree->root);
		cout << endl;
	}	
}*/

