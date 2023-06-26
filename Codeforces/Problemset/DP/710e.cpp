#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e7;
const Lli MAX=1e18;
Lli dp[N+1];
pair<I,Lli>wins[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,x,y;cin>>n>>x>>y;
  fill_n(dp,n+1,MAX);
  dp[0]=0;
  for(I l=0,r=0,i=0;i<=n;i++){
    for(;l<r;l++){
      auto[j,cst]=wins[l];
      if(j>=i)break;
    }
    if(l<r){
      auto[j,cst]=wins[l];
      dp[i]=min(dp[i],(Lli)(j-i)*x+cst);
    }
    if(i<n){
      dp[i+1]=min(dp[i+1],dp[i]+x);
      for(;l<r;r--){
        auto[j,cst]=wins[r-1];
        if(dp[i]+y+(Lli)(2*i-j)*x>cst)break;
      }
      wins[r++]={2*i,dp[i]+y};
    }
  }
  printf("%lli\n",dp[n]);
}