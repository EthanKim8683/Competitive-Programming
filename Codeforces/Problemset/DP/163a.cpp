#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using S=string;

const I N=5000;
const Lli MOD=1e9+7;

Lli dp[N][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  S t;cin>>t;
  I n=s.size(),m=t.size();
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)if(s[i]==t[j])dp[i][j]++;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(i+1<n&&j+1<m&&s[i+1]==t[j+1])(dp[i+1][j+1]+=dp[i][j])%=MOD;
    if(j+1<m)(dp[i][j+1]+=dp[i][j])%=MOD;
  }
  Lli res=0;
  for(I i=0;i<n;i++)(res+=dp[i][m-1])%=MOD;
  printf("%lli\n",res);
}