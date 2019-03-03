#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

class Solution{
public:
	void reOrderArray1(vector<int> &array){
		vector<int> v;
		int p = 0;
		for(int i = 0; i < array.size(); ++i){
			if(array[i] % 2 == 0){
				v.push_back(array[i]);
			}
			else{
				array[p] = array[i];
				++p;
			}
		}
		for(int i = 0; i < v.size(); ++i){
			array[p] = v[i];
			++p;
		}
	}
	void reOrderArray(vector<int> &array){
		int odd = 0;
		for(int i = 0; i < array.size(); ++i){
			if(array[i] % 2 == 1){
				int temp = array[i];
				for(int j = i; j > odd; --j){
					array[j] = array[j - 1];
				}
				array[odd] = temp;
				++odd;
			}
		}
	}
};

int main(){
	Solution *s = new Solution();
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	s->reOrderArray(a);
	for(int i = 0; i < a.size(); ++i){
		cout << a[i] << " ";
	}
	cout << endl;
}

