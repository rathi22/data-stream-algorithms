/*
	Author: Rajat Rathi, CSE Undergraduate at IIT Bombay
*/
#include <bits/stdc++.h>
using namespace std;

// Assuming universe size of N = 2^10 = 1024
int N = 1024;
int LOG_N = 10;
int K = 1024;
int a,b;

// Represents the polynomial: D^10 + D^3 + 1
int poly = 1 + 8 + 1024;

int add(int x, int y){
	return x^y;
}

int mod(int x){
	int dup = x;
	int i=0;
	while(dup>1){
		++i;
		dup >>= 1;
	}

	while(i>=LOG_N){	
		if(x & (1<<i))
			x = add(x,poly*(1<<(i-LOG_N)));
		--i;
	}
	return x;
}

int h(int x){
	int f=0;
	for(int i=0;i<LOG_N;i++)
		if(x & (1<<i))
			f = add(f,a*(1<<i));
	f = add(f,b);
	return mod(f)%K;
}

int zeros(int x){
	int res = 0;
	while(x%2==0){
		++res;
		x >>= 1;
	}
	return res;
}

int main(){
	srand(time(NULL));
	a = rand()%N;
	b = rand()%N;
	int m,j,z=0,p;
	cin>>m;
	while(m--){
		cin>>j;
		p = zeros(h(j));
		cout<<h(j)<<" "<<p<<endl;
		if(p>z)
			z = p;
	}
	int ans = (1<<z)*sqrt(2);
	cout<< ans <<endl;
}