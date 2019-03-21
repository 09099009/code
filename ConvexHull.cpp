#include<cstdio>
#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

struct point{
	int x;
	int y;
	int n;
};

inline bool cmp(const point &p1, const point &p2){
	return p1.x < p2.x || p1.x == p2.x && p1.y < p2.y;
}

inline bool toLeft(const point &p1, const point &p2, const point &p3){
	long long res = (long long)p1.x * (long long)p2.y - (long long)p1.y * (long long)p2.x
	                + (long long)p2.x * (long long)p3.y - (long long)p2.y * (long long)p3.x 
					+ (long long)p3.x * (long long)p1.y - (long long)p3.y * (long long)p1.x;
	return res > 0;
}

vector<int> findConvexHull(vector<point> p, int n){
	vector<int> indices1, indices2, indices3;
	vector<int> flag(n, 0);
	sort(p.begin(), p.end(), cmp);
	for(int i = 0; i < n; ++i){
		if(indices1.size() > 1){
			int ind1 = indices1.back();
			int ind2 = *(indices1.end() - 2);
			if(toLeft(p[ind2], p[ind1], p[i])){
				indices1.pop_back();
				--i;
			}
			else{
				indices1.push_back(i);
			}
		}
		else{
			indices1.push_back(i);
		}
	}
	for(int i = n - 1; i >= 0; --i){
		if(indices2.size() > 1){
			int ind1 = indices2.back();
			int ind2 = *(indices2.end() - 2);
			if(toLeft(p[ind2], p[ind1], p[i])){
				++i;
				indices2.pop_back();
			}
			else{
				indices2.push_back(i);
			}
		}
		else{
			indices2.push_back(i);
		}
	}
	for(int i = 0; i < indices2.size(); ++i){
		int ind = indices2[i];
		if(flag[ind] == 0){
			indices3.push_back(p[ind].n);
			flag[ind] = 1;
		}
	}	
	for(int i = 0; i < indices1.size(); ++i){
		int ind = indices1[i];
		if(flag[ind] == 0){
			indices3.push_back(p[ind].n);
			flag[ind] = 1;
		}
	}

	return indices3;
}

int main(){
	//ios::sync_with_stdio(false);
	int n;
	long long mul;
	point p_tmp;
	vector<point> p;
	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> p_tmp.x >> p_tmp.y;
		p_tmp.n = i + 1;
		p.push_back(p_tmp);
	}
	vector<int> indices = findConvexHull(p, n);
	mul = indices.size();
	for(int i = 0; i < indices.size(); ++i){
		long long ele = indices[i];
		mul = ((mul % (n + 1)) * (ele % (n + 1))) % (n + 1);
	}
	cout << mul << endl;
}

