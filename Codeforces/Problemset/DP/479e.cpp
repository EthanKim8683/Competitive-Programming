#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5000;
const I K=5000;
const Lli MOD=1e9+7;
Lli dp[K+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,a,b,k;cin>>n>>a>>b>>k,a--,b--;
  dp[0][a]=1;
  for(I i=0;i<k;i++){
    for(I j=0;j<n;j++){
      I d=abs(b-j)-1;
      (dp[i+1][max(j-d,0)]+=dp[i][j])%=MOD;
      (dp[i+1][min(j+d,n-1)+1]-=dp[i][j])%=MOD;
    }
    for(I j=0;j<n;j++)(dp[i+1][j+1]+=dp[i+1][j])%=MOD;
    for(I j=0;j<n;j++)(dp[i+1][j]-=dp[i][j])%=MOD;
  }
  Lli res=0;
  for(I i=0;i<n;i++)(res+=dp[k][i])%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}