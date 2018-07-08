/*
	Author: Rajat Rathi, CSE Undergraduate at IIT Bombay
*/

/*  Count Sketch to estimate how many times a value
	appears in a stream.
	The unique property of a sketch is that the result
	by the algorithm for a combination of two streams,
	is a space-efficient combiniation of the results for
	the 2 individual streams   
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
		return mod(f)%K;
	}
};

int main(){
	srand(time(NULL));
	double EPS = 0.2;
	int K = 3/(EPS*EPS);
	int C[K] = {0};
	hashfn h(16384,K,14,17475);
	hashfn g(16384,2,14,17475);

	int m,j,c;	// Length of stream
	cin>>m;
	while(m--){
		// Turnstile Model
		cin>>j>>c;
		C[h.hash(j)] += c*(2*g.hash(j)-1);
	}

	int q,a;	// Number of Queries
	cin>>q;
	while(q--){
		cin>>a;
		cout<<"Frequency="<< (2*g.hash(a)-1)*C[h.hash(a)]<<endl;
	}
}