#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e6;
const Lli MOD=1e9+7;

Lli dp[N+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I t=i%2;
    (dp[i+1][t]+=1)%=MOD;
    (dp[i+1][t]+=dp[i][!t])%=MOD;
    (dp[i+1][0]+=dp[i][0])%=MOD;
    (dp[i+1][1]+=dp[i][1])%=MOD;
  }
  printf("%lli\n",(dp[n][0]+dp[n][1])%MOD);
}