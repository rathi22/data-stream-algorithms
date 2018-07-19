/*
	Author: Rajat Rathi, CSE Undergraduate at IIT Bombay
*/

// AMS algorithm to estimate the kth-frequency-moment
// Median-of-Means technique is used to further improve accuracy of estimate
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Computes a^b
ll pow(ll a, ll b){
	if(b==0)
		return 1;
	ll p = pow(a,b>>1);
	p = p*p;
	if(b&1)
		p = p*a;
	return p;
}

int main(){
	srand(time(NULL));
	// Initialize:
	int t = 5000;	// Number of trials
	int c = 50;
	ll j,k,m;
	ll p[t],r[t],a[t];
	for(int i=0;i<t;i++)
		p[i] = r[i] = a[i] = 0;
	cin>>m>>k;
	
	// Process:
	while(m--){
		cin>>j;
		for(int i=0;i<t;i++){
			++p[i];
			if(rand()%p[i] == 0){
				a[i] = j;
				r[i] = 0;
			}

			if(j == a[i])
				++r[i];
		}
	}

	vector<ll> ans(c,0);
	// Using median-of-means trick
	for(int i=0;i<t;i++)
		ans[i%c] += p[i]*(pow(r[i],k)-pow(r[i]-1,k));
	for(int i=0;i<c;i++)
		ans[i] = ans[i]*c/t;
	sort(ans.begin(),ans.end());

	// Output:
	cout<< ans[c/2] <<endl;
}	