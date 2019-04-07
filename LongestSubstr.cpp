#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
using namespace std;

int lengthOfLongestSubstring(string s){
	int cur_length = 0, max_length = 0, last_position = -1;
	vector<int> flag(128, -1);
	for(string::size_type i = 0; i < s.size(); ++i){
		int asc = static_cast<int>(s[i]);
		if(flag[asc] == -1 || flag[asc] != -1 && flag[asc] < last_position){
			++cur_length;
		}
		else{
			cur_length = i - flag[asc];
			last_position = flag[asc];
		}
		flag[asc] = i;
		if(cur_length > max_length){
			max_length = cur_length;
		}
	}
	return max_length;
}

int main(){
	string s = "123 ";
	cout << lengthOfLongestSubstring(s) << endl;
}

