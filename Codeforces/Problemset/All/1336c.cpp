#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=3000;
const I M=N;
const Lli MOD=998244353;
Lli dp[N+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  S t;cin>>t;
  I n=s.size(),m=t.size();
  for(I i=0;i<n;i++){
    if(i<=n-m)(dp[i][i]+=1)%=MOD;
    for(I j=0;j<=i;j++){
      if(j<n-m||s[n-1-i]==t[n-1-j])(dp[i+1][j+1]+=dp[i][j])%=MOD;
      if(i-j>=m||s[n-1-i]==t[i-j])(dp[i+1][j]+=dp[i][j])%=MOD;
    }
  }
  Lli res=0;
  for(I i=0;i<=n;i++)(res+=dp[n][i])%=MOD;
  printf("%lli\n",res);
}