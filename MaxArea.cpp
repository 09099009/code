#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct Point{
	int x;
	int y;
	Point(const int &_x, const int &_y):x(_x), y(_y){}
};

int maxArea1(vector<int>& height){
	vector<Point> p;
	for(vector<int>::size_type i = 0; i < height.size(); ++i){
		p.push_back(Point(i, height[i]));
	}
	sort(p.begin(), p.end(), [](const Point &p1, const Point &p2){
							   return p1.y > p2.y; });
	for(vector<int>::size_type i = 0; i < p.size(); ++i){
		cout << p[i].x << " " << p[i].y << endl;
	}
	Point pl(0, 0), pr(0, 0), pl_most(0, 0), pr_most(0, 0);
	int area;
	pl = p[0].x < p[1].x ? p[0] : p[1];
	pr = p[0].x > p[1].x ? p[0] : p[1];
	pl_most = pl;
	pr_most = pr;
	int init_height = pl.y < pr.y ? pl.y : pr.y;
	area = init_height * (pr.x - pl.x);
	for(vector<int>::size_type i = 2; i < p.size(); ++i){
		if(p[i].x > pl.x && p[i].x < pr.x){
			continue;
		}
		if(p[i].x < pl.x){
			int cur_area = p[i].y * (pr_most.x - p[i].x);
			if(cur_area > area){
				area = cur_area;
				pl = p[i];
				pr = pr_most;
			}
			pl_most = p[i];
		}
		else if(p[i].x > pr.x){
			int cur_area = p[i].y * (p[i].x - pl_most.x);
			if(cur_area > area){
				area = cur_area;
				pr = p[i];
				pl = pl_most;
			}
			pr_most = p[i];
		}
	}
	return area;
}

int maxArea(vector<int>& height){
	vector<int>::size_type left = 0, right = height.size() - 1;
	unsigned int max_area = 0;
	while(left < right){
		unsigned int width = right - left;
		unsigned int c_height = height[left] <= height[right] ? height[left++] : height[right--];
		unsigned int area = width * c_height;
		max_area = area > max_area ? area : max_area;
	}
	return max_area;
}

int main(){
	vector<int> height = {76, 155, 15, 188, 154, 84, 34, 187, 142, 22, 5, 27, 183, 111, 128, 50, 58, 2, 112, 179, 2, 100, 111, \
	                      115, 76, 134, 120, 118, 103, 31, 146, 58, 198, 134, 38, 104, 170, 25, 92, 112, 199, 49, 140, 135, \
						  160, 20};
	cout << maxArea(height) << endl;
}


