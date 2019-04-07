#include<iostream>
#include<string>
#include<vector>
using namespace std;

string longestPalindrome(string s){
	int max_p = 0, valid_p = 0;
	vector<char> str;
	for(const auto &c : s){
		str.push_back('#');
		str.push_back(c);
	}
	str.push_back('#');
	vector<int> radius(str.size(), 1);
	for(int i = 1; i < str.size(); ++i){
		if(i < valid_p + radius[valid_p]){
			int j = 2 * valid_p - i;
			if(j - radius[j] == valid_p - radius[valid_p]){
				int f = valid_p + radius[valid_p] - i;
				radius[i] = f;
				int l = i - f;
				int r = i + f;
				while(l >= 0 && r < str.size()){
					if(str[l] == str[r]){
						++radius[i];
						--l;
						++r;
					}
					else{
						break;
					}
				}
			}
			else if(j - radius[j] > valid_p - radius[valid_p]){
				radius[i] = radius[j];
			}
			else{
				radius[i] = valid_p + radius[valid_p] - i;
			}
		}
		else{
			int l = i - 1;
			int r = i + 1;
			while(l >= 0 && r < str.size()){
				if(str[l] == str[r]){
					++radius[i];
					--l;
					++r;
				}
				else{
					break;
				}
			}
		}
		if(radius[i] > radius[max_p]){
			max_p = i;
		}
		if(i + radius[i] > valid_p + radius[valid_p]){
			valid_p = i;
		}
	}
	string ret = "";
	for(int i = max_p - radius[max_p] + 1; i < max_p + radius[max_p]; ++i){
		if(str[i] != '#'){
			ret += str[i];
		}
	}
	return ret;
}

string longestPalindrome1(string s){
	int to_front = 0, to_back = 0;
	int cur_length = 0, max_length = 0, start = 0;
	for(int i = 0; i < s.size(); ++i){
		to_front = i - 1;
		to_back = i;
		cur_length = 0;
		while(to_front >= 0 && to_back < s.size()){
			if(s[to_front] == s[to_back]){
				cur_length += 2;
				++to_back;
				--to_front;
			}
			else{
				break;
			}
		}
		if(cur_length > max_length){
			max_length = cur_length;
			start = to_front + 1;
		}
		to_front = i - 2;
		to_back = i;
		cur_length = 0;
		while(to_front >= 0 && to_back < s.size()){
			if(s[to_back] == s[to_front]){
				cur_length += 2;
				++to_back;
				--to_front;
			}
			else{
				break;
			}
		}
		cur_length = (cur_length == 0) ? 0 : cur_length + 1;
		if(cur_length > max_length){
			max_length = cur_length;
			start = to_front + 1;
		}
	}
	if(max_length == 0){
		return string(s.begin(), s.begin() + 1);
	}
	return string(s.begin() + start, s.begin() + start + max_length);
}

int main(){
	string a;
	while(cin >> a){
		string b = longestPalindrome(a);
		cout << b << endl;
	}
}

