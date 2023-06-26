#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
Lli dp[2][N+1];
Lli ress[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  dp[k%2][0]=1;
  for(I i=0;i<n;i+=k,k++)for(I j=i;j<n&&j+k<=n;j++){
    Lli trn=(dp[k%2][j]+dp[1-k%2][j])%MOD;
    (dp[1-k%2][j+k]+=trn)%=MOD;
    (ress[j+k]+=trn)%=MOD;
    dp[k%2][j]=0;
  }
  for(I i=1;i<=n;i++)printf("%lli ",ress[i]);
}