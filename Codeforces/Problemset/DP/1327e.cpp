#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=int64_t;

const I N=2e5;
const Lli MOD=998244353;

Lli dp[N+1][2];
Lli ress[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  dp[1][0]=9*9;
  dp[1][1]=9*10;
  for(I i=1;i<n;i++){
    (dp[i+1][0]+=dp[i][0]*10)%=MOD;
    (dp[i+1][1]+=dp[i][1]*10)%=MOD;
  }
  ress[n]=10;
  for(I i=1;i<n;i++)ress[n-i]=(dp[i][0]*(i-1)+dp[i][1]*2)%MOD;
  for(I i=1;i<=n;i++)printf("%lli ",ress[i]);
}