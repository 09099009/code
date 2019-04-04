#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<limits>
#include<algorithm>
#include<iomanip>
using namespace std;

#define MAXD std::numeric_limits<double>::max();

struct point{
	int64_t x;
	int64_t y;
};

double getDistance(const point &a, const point &b){
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); 
}

void merge(const vector<point> &pset, const int &low, const int &high, double &min_dis){
	int mid = (low + high) / 2;
	int64_t leftInd = pset[mid + 1].x - min_dis;
	int64_t rightInd = min_dis + pset[mid].x;
	vector<point> pl, pr;
	for(int i = mid; i >= low; --i){
		if(pset[i].x >= leftInd){
			pl.push_back(pset[i]);
		}
		else{
			break;
		}
	}
	for(int i = mid + 1; i <= high; ++i){
		if(pset[i].x <= rightInd){
			pr.push_back(pset[i]);
		}
		else{
			break;
		}
	}
	sort(pl.begin(), pl.end(), [](const point &a, const point &b){
								return a.y < b.y; });
	sort(pr.begin(), pr.end(), [](const point &a, const point &b){
								return a.y < b.y; });
	int flag = 0;
	for(int i = 0; i < pl.size(); ++i){
		for(int j = flag; j < pr.size(); ++j){
			if(pr[j].y < pl[i].y - min_dis){
				flag = j + 1;
			}
			else if(pr[j].y > pl[i].y + min_dis){
				break;
			}
			else{
				double new_dis = getDistance(pl[i], pr[j]);
				if(new_dis < min_dis){
					min_dis = new_dis;
				}
			}
		}
		if(flag == pr.size()){
			break;
		}
	}
}

double findClosestPair(const vector<point> &pset, const int &low, const int &high){
	if(high - low == 0){
		return MAXD;
	}
	if(high - low == 1){
		return getDistance(pset[low], pset[high]);
	}
	int mid = (low + high) / 2;
	double dis1 = findClosestPair(pset, low, mid);
	double dis2 = findClosestPair(pset, mid + 1, high);
	double min_dis = min(dis1, dis2);
	merge(pset, low, high, min_dis);
	return min_dis;
}

int main(){
	int n;
	cin >> n;
	vector<point> p_set;
	for(int i = 0; i < n; ++i){
		point temp_p;
		cin >> temp_p.x >> temp_p.y;
		p_set.push_back(temp_p);
	}
	sort(p_set.begin(), p_set.end(), [](const point &a, const point &b){
										return a.x < b.x; });
	cout << fixed << setprecision(2) << findClosestPair(p_set, 0, p_set.size() - 1) << endl;
}
