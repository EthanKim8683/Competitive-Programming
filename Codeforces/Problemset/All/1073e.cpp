#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=18;
const I K=10;
const Lli MOD=998244353;
vector<I>dgts;
pair<Lli,Lli>dp[N+1][1<<K][2];
I k;
pair<Lli,Lli>slv(Lli x){
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(1<<K)*2,pair<Lli,Lli>{0,0});
  dgts.clear();
  for(;x;x/=10)dgts.push_back(x%10);
  reverse(dgts.begin(),dgts.end());
  I n=dgts.size(),upp=dgts[0];
  for(I i=1;i<=upp;i++){
    (dp[1][1<<i][i==upp].first+=i)%=MOD;
    (dp[1][1<<i][i==upp].second+=1)%=MOD;
  }
  for(I i=1;i<n;i++){
    I upp=dgts[i];
    for(I j=1;j<10;j++){
      (dp[i+1][1<<j][0].first+=j)%=MOD;
      (dp[i+1][1<<j][0].second+=1)%=MOD;
    }
    for(I j=0;j<(1<<K);j++){
      for(I k=0;k<10;k++){
        auto[tot,cnt]=dp[i][j][0];
        (dp[i+1][j|1<<k][0].first+=tot*10+cnt*k)%=MOD;
        (dp[i+1][j|1<<k][0].second+=cnt)%=MOD;
      }
      for(I k=0;k<=upp;k++){
        auto[tot,cnt]=dp[i][j][1];
        (dp[i+1][j|1<<k][k==upp].first+=tot*10+cnt*k)%=MOD;
        (dp[i+1][j|1<<k][k==upp].second+=cnt)%=MOD;
      }
    }
  }
  Lli res1=0,res2=0;
  for(I i=0;i<(1<<K);i++)if(__builtin_popcount(i)<=k){
    auto[tot1,cnt1]=dp[n][i][0];  
    auto[tot2,cnt2]=dp[n][i][1];
    (res1+=tot1)%=MOD,(res2+=tot2)%=MOD;
  }
  return{res1,res2};
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli l,r;cin>>l>>r>>k;
  auto[low1,equ1]=slv(l);
  auto[low2,equ2]=slv(r);
  printf("%lli\n",((low2+equ2-low1)%MOD+MOD)%MOD);
}
/*
digit dp
*/