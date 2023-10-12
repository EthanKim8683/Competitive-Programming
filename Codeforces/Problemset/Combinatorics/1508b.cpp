#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I LOGK=61;
Lli dp[N+1];
vector<I>rngs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;Lli k;cin>>n>>k,k--;
    if(n-1<LOGK&&k>>(n-1)){printf("-1\n");continue;}
    rngs.clear(),rngs.push_back(1);
    for(I i=0;i+1<n;i++){
      if(n-2-i>=LOGK||~k>>(n-2-i)&1)rngs.push_back(0);
      rngs.back()++;
    }
    I pre=0;
    for(auto i:rngs){
      pre+=i;
      for(I j=0;j<i;j++)printf("%i ",pre-j);
    }
    printf("\n");
  }
}
/*
we can arithmetic progressions of common difference -1 connected where adjacent
elements are strictly increasing

since adjacent progressions are strictly increasing, the order is always
uniquely defined for an ordered set of progression sizes

this means there are 2 ^ n total almost sorted permutations since, at each
element, we can choose to either increase or decrease

if stored as bits in an integer, where increase is 0 and decrease is 1, the
kth permutation is equal to k - 1 in binary

this is because, for any two permutations, their common prefix bit-wise
corresponds to their common prefix value-wise

however, where they first differ in bit, one permutation must have value
greater than the other to accomodate for a larger arithmetic progression
*/