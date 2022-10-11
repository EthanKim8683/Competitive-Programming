#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I A=1e5;

I dp[N];
I pres[A+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(dp,n,1);
  fill_n(pres,A+1,-1);
  I res=0;
  for(I i=0;i<n;i++){
    I a;cin>>a;
    if(pres[a]!=-1)dp[i]=max(dp[i],dp[pres[a]]+1);
    pres[a]=i;
    for(I j=2;j*j<=a;j++){
      if(a%j)continue;
      I k=a/j;
      if(pres[j]!=-1)dp[i]=max(dp[i],dp[pres[j]]+1);
      pres[j]=i;
      if(j==k)continue;
      if(pres[k]!=-1)dp[i]=max(dp[i],dp[pres[k]]+1);
      pres[k]=i;
    }
    res=max(res,dp[i]);
  }
  printf("%i\n",res);
}