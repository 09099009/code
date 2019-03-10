#include<cstdio>
#include<iostream>
#include<stack>
#include<cstring>
using namespace std;

void quickSort(int x[], int y[], int seq[], int left, int right){
	if(left == right){
		return;
	}
	int i, j, temp1, temp2, temp3;
	i = left;
	j = right;
	temp1 = x[left];
	temp2 = y[left];
	temp3 = seq[left];
	while(i < j){
		while(x[j] >= temp1 && i < j){
			--j;
		}
		while(x[i] <= temp1 && i < j){
			++i;
		}
		if(i < j){
			swap(x[i], x[j]);
			swap(y[i], y[j]);
			swap(seq[i], seq[j]);
		}
	}
	x[left] = x[i];
	x[i] = temp1;
	y[left] = y[i];
	y[i] = temp2;
	seq[left] = seq[i];
	seq[i] = temp3;
	if(i > left){
		quickSort(x, y, seq, left, i - 1);
	}
	if(i < right){
		quickSort(x, y, seq, i + 1, right);
	}
}

bool toLeft(int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y){
	return p1_x * p2_y - p1_y * p2_x + p2_x * p3_y - p2_y * p3_x + p3_x * p1_y - p3_y * p1_x > 0;
}

stack<int> findConvexHull(int x[], int y[], int n){
	stack<int> indices1, indices2, indices3;
	int flag[n];
	int seq[n];
	for(int i = 0; i < n; ++i){
		flag[i] = 0;
		seq[i] = i;
	}
	quickSort(x, y, seq, 0, n - 1);
	int boun1 = 0, boun2 = 0;
	for(int i = 1; i < n; ++i){
		if(x[i] == x[i - 1]){
			boun2 = i;
		}
		else{
			quickSort(y, x, seq, boun1, boun2);
			boun1 = i;
		}
	}
	for(int i = 0; i < n; ++i){
		cout << x[i] << " " << y[i] << endl;
	}
	indices1.push(0);
	indices1.push(1);
	for(int i = 2; i < n; ++i){
		int ind1 = indices1.top();
		indices1.pop();
		int ind2 = indices1.top();
		if(toLeft(x[ind2], y[ind2], x[ind1], y[ind1], x[i], y[i])){
			if(indices1.size() == 1){
				indices1.push(i);
			}
			else{
				--i;
			}
		}
		else{
			indices1.push(ind1);
			indices1.push(i);
		}
	}
	indices2.push(n - 1);
	indices2.push(n - 2);
	for(int i = n - 3; i >= 0; --i){
		int ind1 = indices2.top();
		indices2.pop();
		int ind2 = indices2.top();
		if(toLeft(x[ind2], y[ind2], x[ind1], y[ind1], x[i], y[i])){
			if(indices2.size() == 1){
				indices2.push(i);
			}		
			else{
				++i;
			}
		}
		else{
			indices2.push(ind1);
			indices2.push(i);
		}
	}
	while(!indices2.empty()){
		int ind = indices2.top();
		if(flag[ind] == 0){
			indices3.push(seq[ind] + 1);
			flag[ind] = 1;
		}
		indices2.pop();
	}	
	while(!indices1.empty()){
		int ind = indices1.top();
		if(flag[ind] == 0){
			indices3.push(seq[ind] + 1);
			flag[ind] = 1;
		}
		indices1.pop();
	}

	return indices3;
}

int main(){
	int n, count = 0, mul;
	cin >> n;
	int x[n], y[n];
	for(int i = 0; i < n; ++i){
		cin >> x[i] >> y[i];
	}
	stack<int> indices = findConvexHull(x, y, n);
	mul = indices.size();
	while(!indices.empty()){
		int ele = indices.top();
		cout << ele << endl;
		mul = ((mul % (n + 1)) * (ele % (n + 1))) % (n + 1);
		indices.pop();
	}
	cout << mul << endl;
}

