#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2000;
const I K=N-1;
const Lli MOD=998244353;

Lli dp[N][K+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  dp[0][0]=m;
  for(I i=0;i+1<n;i++){
    for(I j=0;j<=k;j++){
      if(j+1<=k)(dp[i+1][j+1]+=dp[i][j]*(m-1))%=MOD;
      (dp[i+1][j]+=dp[i][j])%=MOD;
    }
  }
  printf("%lli\n",dp[n-1][k]);
}