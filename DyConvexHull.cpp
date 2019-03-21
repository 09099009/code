#include<iostream>
#include "AvlTree.h"
using namespace std;

#define MAX 1000001
#define MIN -1000001

bool toLeft(const Point &p1, const Point &p2, const Point &p3){
	long long res = (long long)p1.x * (long long)p2.y - (long long)p1.y * (long long)p2.x
		            + (long long)p2.x * (long long)p3.y - (long long)p2.y * (long long)p3.x
				    + (long long)p3.x * (long long)p1.y - (long long)p3.y * (long long)p1.x;
  	return res > 0;
}

Point FindNext(const AvlNode *t, Point p){
	Point tmp(MAX, MAX);
	while(t != NULL){
		if(p.x < t->data.x){
			if(t->data.x < tmp.x){
				tmp = t->data;
			}
			t = t->left;	
		}
		else{
			t = t->right;
		}
	}
	return tmp;
}

Point FindLast(const AvlNode *t, Point p){
	Point tmp(MIN, MIN);
	while(t != NULL){
		if(p.x > t->data.x){
			if(t->data.x > tmp.x){
				tmp = t->data;
			}
			t = t->right;
		}
		else{
			t = t->left;
		}
	}
	return tmp;
}

bool Find(const AvlNode *t, const Point &p, Point &pp){
	while(t != NULL){
		if(p.x == t->data.x){
			pp = t->data;
			return true;
		}
		else if(p.x < t->data.x){
			t = t->left;
		}
		else{
			t = t->right;
		}
	}
	return false;
}

void LTR_Upper(AvlTree *t, Point p){
	Point p1 = FindNext(t->root, p);
	if(p1.x == MAX){
		return;
	}
	Point p2 = FindNext(t->root, p1);
	while(p2.x != MAX){
		if(toLeft(p, p1, p2)){
			t->Delete(t->root, p1);
			p1 = p2;
			p2 = FindNext(t->root, p1);
		}
		else{
			break;
		}
	}
}

void RTL_Upper(AvlTree *t, Point p){
	Point p1 = FindLast(t->root, p);
	if(p1.x == MIN){
		return;
	}
	Point p2 = FindLast(t->root, p1);
	while(p2.x != MIN){
		if(toLeft(p2, p1, p)){
			t->Delete(t->root, p1);
			p1 = p2;
			p2 = FindLast(t->root, p1);
		}
		else{
			break;
		}
	}
}

void LTR_Lower(AvlTree *t, Point p){
	Point p1 = FindNext(t->root, p);
	if(p1.x == MAX){
		return;
	}
	Point p2 = FindNext(t->root, p1);
	while(p2.x != MAX){
		if(toLeft(p2, p1, p)){
			t->Delete(t->root, p1);
			p1 = p2;
			p2 = FindNext(t->root, p1);
		}
		else{
			break;
		}
	}
}

void RTL_Lower(AvlTree *t, Point p){
	Point p1 = FindLast(t->root, p);
	if(p1.x == MIN){
		return;
	}
	Point p2 = FindLast(t->root, p1);
	while(p2.x != MIN){
		if(toLeft(p, p1, p2)){
			t->Delete(t->root, p1);
			p1 = p2;
			p2 = FindLast(t->root, p1);
		}
		else{
			break;
		}
	}
}

void UpdateAvl(Point &lu, Point &ll, Point &ru, Point &rl, const Point &p,  AvlTree *&upperConv, AvlTree *&lowerConv){
	if(p.x < lu.x && p.x > ru.x){
		lu.x = p.x, lu.y = p.y, ll.x = p.x, ll.y = p.y;
		ru.x = p.x, ru.y = p.y, rl.x = p.x, rl.y = p.y;
		upperConv->Insert(upperConv->root, lu);
		lowerConv->Insert(lowerConv->root, ll);
	}
	else if(p.x < lu.x){
		lu.x = p.x;
		lu.y = p.y;
		ll.x = p.x;
		ll.y = p.y;
		upperConv->Insert(upperConv->root, lu);
		lowerConv->Insert(lowerConv->root, ll);
		LTR_Upper(upperConv, lu);
		LTR_Lower(lowerConv, ll);
	}
	else if(p.x == lu.x){
		if(p.y > lu.y){
			upperConv->Delete(upperConv->root, lu);
			lu.y = p.y;
			upperConv->Insert(upperConv->root, lu);
			LTR_Upper(upperConv, lu);
		}
		else if(p.y < ll.y){
			lowerConv->Delete(lowerConv->root, ll);
			ll.y = p.y;
			lowerConv->Insert(lowerConv->root, ll);
			LTR_Lower(lowerConv, ll);
		}
	}
	else if(p.x == ru.x){
		if(p.y > ru.y){
			upperConv->Delete(upperConv->root, ru);
			ru.y = p.y;
			upperConv->Insert(upperConv->root, ru);
			RTL_Upper(upperConv, ru);
		}
		else if(p.y < rl.y){
			lowerConv->Delete(lowerConv->root, rl);
			rl.y = p.y;
			lowerConv->Insert(lowerConv->root, rl);
			RTL_Lower(lowerConv, rl);
		}
	}
	else if(p.x > ru.x){
		ru.x = p.x;
		ru.y = p.y;
		rl.x = p.x;
		rl.y = p.y;
		upperConv->Insert(upperConv->root, ru);
		lowerConv->Insert(lowerConv->root, rl);
		RTL_Upper(upperConv, ru);
		RTL_Lower(lowerConv, rl);
	}
	else{
		Point tmp(0, 0);
		Point p1 = FindLast(upperConv->root, p);
		Point p2 = FindNext(upperConv->root, p);
		if(Find(upperConv->root, p, tmp)){
			if(toLeft(tmp, p2, p)){
				upperConv->Delete(upperConv->root, tmp);
				upperConv->Insert(upperConv->root, p);
				LTR_Upper(upperConv, p);
				RTL_Upper(upperConv, p);
			}
		}
		else{
			if(toLeft(p1, p2, p)){
				upperConv->Insert(upperConv->root, p);
				LTR_Upper(upperConv, p);
				RTL_Upper(upperConv, p);
			}
		}
		p1 = FindLast(lowerConv->root, p);
		p2 = FindNext(lowerConv->root, p);
		if(Find(lowerConv->root, p, tmp)){
			if(toLeft(p2, tmp, p)){
				lowerConv->Delete(lowerConv->root, tmp);
				lowerConv->Insert(lowerConv->root, p);
				LTR_Lower(lowerConv, p);
				RTL_Lower(lowerConv, p);
			}
		}
		else{
			if(toLeft(p2, p1, p)){
				lowerConv->Insert(lowerConv->root, p);
				LTR_Lower(lowerConv, p);
				RTL_Lower(lowerConv, p);
			}
		}
	}
}

bool Search(const Point &lu, const Point &ll, const Point &ru, const Point &rl, const Point &p, const AvlTree *upperConv, const AvlTree *lowerConv){
	if(p.x < lu.x || p.x > ru.x){
		return false;
	}
	else if(p.x == lu.x){
		if(p.y >= ll.y && p.y <= lu.y){
			return true;
		}
		else{
			return false;	
		}
	}
	else if(p.x == ru.x){
		if(p.y >= rl.y && p.y <= ru.y){
			return true;
		}
		else{
			return false;
		}
	}
	Point tmp(0, 0);
	Point p1 = FindLast(upperConv->root, p);
	Point p2 = FindNext(upperConv->root, p);
	if(Find(upperConv->root, p, tmp)){
		p1 = tmp;
	}
	if(toLeft(p1, p2, p)){
		return false;
	}
	p1 = FindLast(lowerConv->root, p);
	p2 = FindNext(lowerConv->root, p);
	if(Find(lowerConv->root, p, tmp)){
		p1 = tmp;
	}
	if(toLeft(p2, p1, p)){
		return false;
	}
	return true;
}

int main(){
	Point lu(MAX, MAX);
	Point ll(MAX, MAX);
	Point ru(MIN, MIN);
	Point rl(MIN, MIN);
	AvlTree *upperConv = new AvlTree();
	AvlTree *lowerConv = new AvlTree();
	int n, operation;
	Point p(0, 0);
	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> operation >> p.x >> p.y;
		if(operation == 1){
			UpdateAvl(lu, ll, ru, rl, p, upperConv, lowerConv);
		}
		else if(operation == 2){
			if(Search(lu, ll, ru, rl, p, upperConv, lowerConv)){
				cout << "YES" << endl;
			}
			else{
				cout << "NO" << endl;
			}
		}
		else{
		
		}
	}
}

