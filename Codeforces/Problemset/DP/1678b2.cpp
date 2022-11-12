#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=2e5;
const I MAX=1e9;

I ps[N+1];
pair<I,I>dp[N+1][2];

void cmb(pair<I,I>&a,pair<I,I>b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    fill_n(ps,n+1,0);
    for(I i=0;i<n;i++)ps[i+1]=s[i]-'0';
    for(I i=0;i<n;i++)ps[i+1]+=ps[i];
    for(I i=0;i<=n;i++)dp[i][0]=dp[i][1]={MAX,MAX};
    dp[0][0]=dp[0][1]={0,1};
    for(I i=0;i<=n;i++){
      auto[sum0,sub0]=dp[i][0];
      auto[sum1,sub1]=dp[i][1];
      cmb(dp[i+2][0],{sum0+ps[i+2]-ps[i],sub0});
      cmb(dp[i+2][1],{sum0+2-(ps[i+2]-ps[i]),sub0+1});
      cmb(dp[i+2][0],{sum1+ps[i+2]-ps[i],sub1+1});
      cmb(dp[i+2][1],{sum1+2-(ps[i+2]-ps[i]),sub1});
    }
    auto[sum,sub]=min(dp[n][0],dp[n][1]);
    printf("%i %i\n",sum,sub);
  }
}