#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1000;
const I M=1000;
const I K=1000;
const Lli MOD=1e9+7;
Lli dp[N+1][K+1];
Lli ps[N+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=1;i<=max(n-2,m-2);i++){
    (dp[i][1]+=1)%=MOD;
    for(I j=0;j<=k;j++){
      if(i>=3&&j+1<=k)(dp[i][j+1]+=ps[i-2][j])%=MOD;
      (dp[i+1][j]+=dp[i][j])%=MOD;
      (ps[i][j]+=dp[i][j])%=MOD;
      (ps[i+1][j]+=ps[i][j])%=MOD;
    }
  }
  printf("%lli\n",ps[n-2][k]*ps[m-2][k]%MOD);
}