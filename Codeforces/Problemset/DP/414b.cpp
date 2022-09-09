#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2000,K=2000;
const Lli MOD=1e9+7;

Lli dp[K+1][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  dp[0][1]=1;
  for(I i=0;i<k;i++)for(I j=1;j<=n;j++)for(I l=j;l<=n;l+=j)
    (dp[i+1][l]+=dp[i][j])%=MOD;
  Lli res=0;
  for(I i=1;i<=n;i++)(res+=dp[k][i])%=MOD;
  printf("%lli\n",res);
  return 0;
}