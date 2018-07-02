/*
	Author: Rajat Rathi, CSE Undergraduate at IIT Bombay
*/

// AMS algorithm to estimate the number of distinct elements
#include <bits/stdc++.h>
using namespace std;

// Assuming universe size of N = 2^10 = 1024
// Building a function from a  2-universal hash family
int N = 1024;
int LOG_N = 10;
int K = 1024;
int a,b;

// Represents the polynomial: D^10 + D^3 + 1
int poly = 1 + 8 + 1024;

// Polynomial addition
int add(int x, int y){
	return x^y;
}

// Polynomial modulo
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

// Hash function from 2-universal hash family
int h(int x){
	int f=0;
	for(int i=0;i<LOG_N;i++)
		if(x & (1<<i))
			f = add(f,a*(1<<i));
	f = add(f,b);
	return mod(f)%K;
}

// zeros(p) = max{i: 2^i | p}
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
		cout<<"Hashed Value: "<<h(j)<<", Zeros: "<<p<<endl;
		if(p>z)
			z = p;
	}
	// Our estimate for number of distinct elements
	int ans = (1<<z)*sqrt(2);
	cout<< "Ans: " << ans <<endl;
}