/*
	Author: Rajat Rathi, CSE Undergraduate at IIT Bombay
*/
#include <bits/stdc++.h>
using namespace std;

/* Finding all elements in stream which occur more than m/k times
   using Misra-Gries algorithm (deterministic) with parameter k. */ 
// Input: m and k, and then a corresponding stream of m integers.

int main(){
	int m,k;
	cin>>m>>k;
	/* Input data is being stored only for verification in second pass. 
		No need to store if access to the same stream is granted again */
	int a[m];
	for(int i=0;i<m;i++)
		cin>>a[i];

	int j,size=0;
	map<int,int> keys;
	map<int,int>::iterator it;
	
	// First Pass
	for(int i=0;i<m;i++){
		// cin>>j;
		j=a[i];
		if(keys.count(j))
			++keys[j];
		else if(size<k-1){
			keys[j]=1;
			++size;
		//	cout<<"Added "<<j<<endl;
		}
		else{
			for(it = keys.begin(); it != keys.end(); ++it){
				cout<< it->first <<" "<< it->second <<endl;
				if(it->second == 1){
		//			cout<<"Removed "<< it->first <<endl;
					keys.erase(it);
					--size;
				}
				else
					--(it->second);
			}
		}
	}

	/*	Frequency of any element not in the set is to be treated as zero.
		Hence, the above procedure gives an estimate fj' such that for any element j,
		fj - m/k <= fj' <= fj, where fj is the actual frequency of j in the stream. */

	// Any element occuring with frequency more than m/k times must be present in this map.
	cout<<"At the end of first pass...\n";
	for(it = keys.begin(); it != keys.end(); it++){
		cout<< "Element: "<< it->first <<" Frequency:"<< it->second <<endl;	// Elements present in the map, and their frequencies.
		it->second = 0;	// Initialization for Second pass.
	}

	// A second pass over the same stream to calculate exact frequencies of the elements in question.
	for(int i=0;i<m;i++){
		j = a[i];
		if(keys.count(j))
			++keys[j];
	}

	// Printing all "frequent elements".
	cout<<"\"Frequent\" elements: ";
	int flag = 1;
	for(it = keys.begin(); it != keys.end(); it++){
		if(it->second > m/k){
			cout<< it->first <<" ";
			flag = 0;
		}
	}
	if(flag)
		cout<<"NONE";
	cout<<endl;	
}
