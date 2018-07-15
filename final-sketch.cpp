/*
	Author: Rajat Rathi, CSE Undergraduate at IIT Bombay
*/

/*  Count Sketch to estimate how many times a value
	appears in a stream.
	The unique property of a sketch is that the result
	by the algorithm for a combination of two streams,
	is a space-efficient combiniation of the results for
	the 2 individual streams.
	Final Sketch simply improves upon Count Sketch
	by giving a epsilon-delta approximation using the 
	Median Trick.   
	*/
#include <bits/stdc++.h>
using namespace std;

// Structure for 2-universal hash function
struct hashfn{
	int N,K,LOG_N,POLY,a,b;

	hashfn(){
		N = 16384;
		K = 2;
		LOG_N = 14;
		POLY = 17475;
		a = rand()%N;
		b = rand()%N;
	}

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
	double EPS = 1;
	int K = 3/(EPS*EPS);
	int t = 100;	// Variable Parameter Depending upon delta
	int C[t][K] = {0};
	hashfn h[t];
	hashfn g[t];
	for(int i=0;i<t;i++)
		h[i].K = K;

	int m,j,c;	// Length of stream
	cin>>m;
	while(m--){
		// Turnstile Model
		cin>>j>>c;
		for(int i=0;i<t;i++)
			C[i][h[i].hash(j)] += c*(2*g[i].hash(j)-1);
	}

	int v[t];
	int q,a;	// Number of Queries
	cin>>q;
	while(q--){
		cin>>a;
		for(int i=0;i<t;i++)
			v[i] = (2*g[i].hash(a)-1)*C[i][h[i].hash(a)];
		sort(v,v+t);
		cout<<"Frequency="<< v[t/2] <<endl;
	}
}