#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

vector<I>adjs[N];
pair<Lli,Lli>rngs[N];
Lli dp[N];
I res=0;

Lli dfs(I a){
  Lli cur=0;
  for(auto b:adjs[a])cur+=dfs(b);
  auto[l,r]=rngs[a];
  dp[a]=min(cur,r);
  if(dp[a]<l)dp[a]=r,res++;
  return dp[a];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=1;i<n;i++){
      I p;cin>>p,p--;
      adjs[p].push_back(i);
    }
    for(I i=0;i<n;i++){
      I l,r;cin>>l>>r;
      rngs[i]={l,r};
    }
    res=0,dfs(0);
    printf("%i\n",res);
  }
}