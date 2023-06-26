#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I K=2000;
const Lli MOD=1e9+7;
Lli dp[K+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  S s;cin>>s;
  I k=n-m;
  dp[0][0]=1;
  for(I i=0;i<k;i++)for(I j=0;j<=k;j++){
    if(j+1<=k)(dp[i+1][j+1]+=dp[i][j])%=MOD;
    if(j-1>=0)(dp[i+1][j-1]+=dp[i][j])%=MOD;
  }
  I low=0,upp=0;
  for(auto c:s)upp+=(c=='(')-(c==')'),low=min(low,upp);
  Lli res=0;
  for(I i=0;i<=k;i++)for(I j=-low;j<=k;j++)if(j+upp<=k)(res+=dp[i][j]*dp[k-i][j+upp])%=MOD;
  printf("%lli\n",res);
}