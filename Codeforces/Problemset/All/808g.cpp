#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
using Lli=long long int;
const I M=1e5;
const I MIN=-1e9;
const Lli BAS=(1ll<<17)-1;
const Lli MOD=(1ll<<31)-1;
vector<vector<I>>dp;
Lli hshs[M+1];
Lli pows[M+1];
B equs[M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  S t;cin>>t;
  I n=s.size(),m=t.size();
  pows[0]=1;
  for(I i=1;i<=m;i++)pows[i]=pows[i-1]*BAS%MOD,hshs[i]=(hshs[i-1]*BAS+t[i-1])%MOD;
  for(I i=0;i<=m;i++)equs[i]=hshs[i]==((hshs[m]-hshs[m-i]*pows[i])%MOD+MOD)%MOD;
  dp.resize(n+1);
  for(I i=0;i<=n;i++)dp[i].resize(m+1,MIN);
  dp[0][0]=0;
  for(I i=0;i+m<=n;i++){
    B equ=1;
    for(I j=m-1;j>=0;j--){
      equ&=s[i+j]==t[j]||s[i+j]=='?';
      if(equs[j]&&equ)dp[i+1][m-1]=max(dp[i+1][m-1],dp[i][j]+1);
      dp[i+1][max(j-1,0)]=max(dp[i+1][max(j-1,0)],dp[i][j]);
    }
  }
  I res=0;
  for(I i=0;i<=n;i++)for(I j=0;j<=m;j++)res=max(res,dp[i][j]);
  printf("%i\n",res);
}
/*
we can use dynamic programming, where, for each index i, we store by length of
substring beginning at i which is also a suffix of t

each transition transitions to length |t| - 1 and checks if it is possible to
change the string's characters such that, prefixed by the aforementioned
substring, t can be formed
*/