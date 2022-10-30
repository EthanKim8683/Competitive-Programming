#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e6;
const I A=1e6;

B viss[A+1];
I dp[A+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a;cin>>a;
    viss[a]=1,dp[a]=1;
  }
  I res=1;
  for(I i=1;i<=A;i++)if(viss[i])
    for(I j=2*i;j<=A;j+=i)if(viss[j])
      res=max(res,dp[j]=max(dp[j],dp[i]+1));
  printf("%i\n",res);
}