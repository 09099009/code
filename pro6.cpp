#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

class Solution{
public:
	int minNumberInRotateArray1(vector<int> rotateArray){
		int i = 0;
		for(; i < rotateArray.size() - 1; ++i){
			if(rotateArray[i] > rotateArray[i + 1]){
				return rotateArray[i + 1];
			}
		}		
		if(rotateArray.size() > 0){
			return rotateArray[0];
		}
		return 0;
	}
	int minNumberInRotateArray(vector<int> rotateArray){
		if(rotateArray.size() == 0){
			return 0;
		}
		int min_ele = 0;
		int low = 0, high = rotateArray.size() - 1;
		while(low <= high){
			int mid = (low + high) / 2;
			if(mid == 0){
				if(high == 0){
					min_ele = rotateArray[0];
				}
				else{
					min_ele = min(rotateArray[0], rotateArray[1]);
				}
			}
			else{
				if(rotateArray[mid - 1] > rotateArray[mid]){
					min_ele = rotateArray[mid];
					break;
				}
				else if(rotateArray[mid] > rotateArray[0]){
					low = mid + 1;
				}
				else if(rotateArray[mid] < rotateArray[0]){
					high = mid - 1;
				}
				else{
					if(rotateArray[mid] > rotateArray[rotateArray.size() - 1]){
						low = mid + 1;
					}
					else if(rotateArray[mid] < rotateArray[rotateArray.size() - 1]){
						min_ele = rotateArray[0];
						break;
					}
					else{
						min_ele = minNumberInRotateArray1(rotateArray);
						break;
					}
				}
			}
		}

		return min_ele;
	}
};

int main(){
	Solution *s = new Solution();
	vector<int> rotateArray;
	rotateArray.push_back(3);
	rotateArray.push_back(4);
	rotateArray.push_back(5);
	rotateArray.push_back(1);
	rotateArray.push_back(2);
	cout << s->minNumberInRotateArray(rotateArray) << endl;
}

