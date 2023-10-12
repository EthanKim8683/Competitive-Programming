#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=3e5;
const I M=3e5;
const Lli MOD=998244353;
S brds[N];
pair<Lli,Lli>dp[M+1][2];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>brds[i];
  I tot=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)if(brds[i][j]=='o')tot++;
  Lli res=0;
  for(I i=0;i<n;i++){
    I cur=0;
    for(I j=0;j<=m;j++)fill_n(dp[j],2,pair<Lli,Lli>{0,0});
    dp[0][0]={0,1};
    for(I j=0;j<m;j++){
      auto[tot1,cnt1]=dp[j][0];
      auto[tot2,cnt2]=dp[j][1];
      (dp[j+1][0].first+=tot1)%=MOD;
      (dp[j+1][0].second+=cnt1)%=MOD;
      (dp[j+1][0].first+=tot2)%=MOD;
      (dp[j+1][0].second+=cnt2)%=MOD;
      if(brds[i][j]=='o'){
        (dp[j+1][1].first+=tot1)%=MOD;
        (dp[j+1][1].second+=cnt1)%=MOD;
        (dp[j+1][0].first+=tot2+cnt2)%=MOD;
        (dp[j+1][0].second+=cnt2)%=MOD;
        cur++;
      }
    }
    (res+=(dp[m][0].first+dp[m][1].first)*mpw(2,tot-cur))%=MOD;
  }
  for(I i=0;i<m;i++){
    I cur=0;
    for(I j=0;j<=n;j++)fill_n(dp[j],2,pair<Lli,Lli>{0,0});
    dp[0][0]={0,1};
    for(I j=0;j<n;j++){
      auto[tot1,cnt1]=dp[j][0];
      auto[tot2,cnt2]=dp[j][1];
      (dp[j+1][0].first+=tot1)%=MOD;
      (dp[j+1][0].second+=cnt1)%=MOD;
      (dp[j+1][0].first+=tot2)%=MOD;
      (dp[j+1][0].second+=cnt2)%=MOD;
      if(brds[j][i]=='o'){
        (dp[j+1][1].first+=tot1)%=MOD;
        (dp[j+1][1].second+=cnt1)%=MOD;
        (dp[j+1][0].first+=tot2+cnt2)%=MOD;
        (dp[j+1][0].second+=cnt2)%=MOD;
        cur++;
      }
    }
    (res+=(dp[n][0].first+dp[n][1].first)*mpw(2,tot-cur))%=MOD;
  }
  printf("%lli\n",res);
}
/*
we can greedily place dominoes given a board of black, red and blue tiles

the number of horizontal dominoes per row is the total among all contiguous
ranges of red tiles l / 2, where l is the length of the range

the number of vertical dominoes per row is the total among all contgiguous
ranges of blue tiles l / 2, where h is the length of the range

with this, we can independently count the contribution of each row and column
using dynamic programming
*/