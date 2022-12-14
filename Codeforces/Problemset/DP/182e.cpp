#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
const I L=3000;
const Lli MOD=1e9+7;
pair<I,I>brds[N];
Lli dp[L+1][N][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,l;cin>>n>>l;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    brds[i]={a,b};
  }
  for(I i=0;i<n;i++){
    auto[a,b]=brds[i];
    if(b<=l)dp[b][i][0]++;
    if(a==b)continue;
    if(a<=l)dp[a][i][1]++;
  }
  for(I i=0;i<l;i++)for(I j=0;j<n;j++){
    for(I k=0;k<n;k++){
      if(j==k)continue;
      auto[a1,b1]=brds[j];
      auto[a2,b2]=brds[k];
      if(b1==a2&&i+b2<=l)(dp[i+b2][k][0]+=dp[i][j][0])%=MOD;
      if(a1==a2&&i+b2<=l)(dp[i+b2][k][0]+=dp[i][j][1])%=MOD;
      if(a2==b2)continue;
      if(b1==b2&&i+a2<=l)(dp[i+a2][k][1]+=dp[i][j][0])%=MOD;
      if(a1==b2&&i+a2<=l)(dp[i+a2][k][1]+=dp[i][j][1])%=MOD;
    }
  }
  Lli res=0;
  for(I i=0;i<n;i++)for(I j=0;j<2;j++)(res+=dp[l][i][j])%=MOD;
  printf("%lli\n",res);
}