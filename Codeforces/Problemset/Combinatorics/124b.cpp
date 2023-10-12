#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=8;
const I K=8;
const I MAX=1e9;
C dgts[N+1][K+1];
I inds[K];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>dgts[i];
  I res=MAX;
  iota(inds,inds+k,0);
  do{
    I upp=0,low=MAX;
    for(I i=0;i<n;i++){
      I cur=0;
      for(I j=0;j<k;j++)cur*=10,cur+=dgts[i][inds[j]]-'0';
      upp=max(upp,cur),low=min(low,cur);
    }
    res=min(res,upp-low);
  }while(next_permutation(inds,inds+k));
  printf("%i\n",res);
}
/*
we can brute force for each permutation
*/