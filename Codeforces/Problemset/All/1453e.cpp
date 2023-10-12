#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I MAX=1e9;
vector<I>adjs[N];
I dp[N];
I n;
B dfs(I k,I a,I p=-1){
  dp[a]=MAX;
  B lea=1;
  for(auto b:adjs[a])if(b!=p){
    lea=0;
    if(!dfs(k,b,a))return 0;
    if(dp[b]+2>k)return 0;
    dp[a]=min(dp[a],dp[b]+1);
  }
  if(lea)dp[a]=0;
  return 1;
}
B chk(I k){
  I cnt=0;
  for(auto b:adjs[0]){
    if(!dfs(k,b,0))return 0;
    if(dp[b]+2>k)cnt++;
  }
  return cnt<=1;
}
I fnd(){
  I l=1,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    printf("%i\n",fnd());
  }
}
/*
we can binary search for k using tree dynamic programming to check, keeping
track of the distance to the optimal node upon which Badugi lands on after
traversing the entire subtree and failing whenever this distance is greater
than k
*/