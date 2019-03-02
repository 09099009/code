#include<cstdio>
#include<iostream>
using namespace std;

class Solution{
public:
	int NumberOf1(int n){
		if(n == -2147483648){
			return 1;
		}
		bool conti = true, isn = false;
		int num_one = 0, num_zero = 0;
		if(n < 0){
			isn = true;
			n = -n;
		}
		while(n > 0){
			if(n % 2 == 1){
				num_one += 1;
				conti = false;
			}
			else{
				if(conti == true){
					num_zero += 1;
				}
			}
			n /= 2;
		}
		if(!isn){
			return num_one;
		}
		else{
			return 33 - num_one - num_zero;
		}
	}
};

int main(){
	Solution *s = new Solution();
	cout << s->NumberOf1(1) << endl;
	cout << s->NumberOf1(5) << endl;
	cout << s->NumberOf1(12) << endl;
	cout << s->NumberOf1(-1) << endl;
	cout << s->NumberOf1(-10) << endl;
	cout << s->NumberOf1(-20) << endl;
}


