/*
	Author: Rajat Rathi, CSE Undergraduate at IIT Bombay
*/

/* BJKST algorithm to estimate the number of distinct elements:
	This is an (epsilon,delta) approximation algorithm as opposed to
	the previous AMS algorithm for the same problem.
	*/	
#include <bits/stdc++.h>
using namespace std;

// Structure for 2-universal hash function
struct hashfn{
	int N,K,LOG_N,POLY,a,b;
	hashfn(int n, int k, int logn, int poly){
		N = n;
		K = k;
		LOG_N = logn;
		POLY = poly;
		a = rand()%N;
		b = rand()%N;
	}

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
				x = add(x,POLY*(1<<(i-LOG_N)));
			--i;
		}
		return x;
	}

	int hash(int x){
		int f=0;
		for(int i=0;i<LOG_N;i++)
			if(x & (1<<i))
				f = add(f,a*(1<<i));
		f = add(f,b);
		return mod(f)%K+1;
	}
};

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
	// Constants
	double EPS = 1.0;
	int c = 48;
	int b = 36;

	// Initialization:
	int MAX = c/(EPS*EPS);
	hashfn h(16384,16384,14,17475);
	hashfn g(16384,(int)(b*14*14/EPS),14,17475);
	int z = 0;
	set<pair<int,int> > B;
	set<pair<int,int> >::iterator it;

	// Process:
	int m,j,p;
	cin>>m;
	while(m--){
		cin>>j;
		p = zeros(h.hash(j));
		if(p>=z){
			B.insert(make_pair(p,g.hash(j)));
			cout<<"j="<<j<<" p="<<p<<endl;
			while(B.size()>=MAX){
				++z;
				cout<<"Increment\n";
				for(it = B.begin(); it != B.end(); it++)
					if((it->first) >= z)
						break;
				B.erase(B.begin(),it);	
			}
		}
	}

	// Output:
	cout<< B.size()*(1<<z) <<endl;
	/* Accuracy of output can be improved by using
		the Median Trick. (Can be found in 'distinct-elements.cpp')
	*/
}