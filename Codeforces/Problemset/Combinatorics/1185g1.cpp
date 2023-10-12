#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=15;
const I G=3;
const I T=225;
const Lli MOD=1e9+7;
pair<I,I>sngs[N];
Lli dp[1<<N][G][T+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,t;cin>>n>>t;
  for(I i=0;i<n;i++){
    I d,g;cin>>d>>g,g--;
    sngs[i]={d,g};
    if(d>t)continue;
    dp[1<<i][g][d]=1;
  }
  for(I i=1;i<(1<<n);i++)for(I j=0;j<G;j++)for(I k=0;k<=t;k++)for(I l=0;l<n;l++)if(~i>>l&1){
    auto[d,g]=sngs[l];
    if(g==j||k+d>t)continue;
    (dp[i|1<<l][g][k+d]+=dp[i][j][k])%=MOD;
  }
  Lli res=0;
  for(I i=0;i<(1<<n);i++)for(I j=0;j<G;j++)(res+=dp[i][j][t])%=MOD;
  printf("%lli\n",res);
}
/*
we can find the number of valid sequences using bitmask dynamic programming
*/