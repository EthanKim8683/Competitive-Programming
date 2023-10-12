#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e5;
const I M=N;
const I X=30;
const Lli MOD=(1ll<<31)-1;
const Lli BAS=(1ll<<17)-1;
Lli pows[N+1];
Lli hshs[2][N+1];
I dp[N+1][X+1];
Lli qry(I t,I i,I len){
  return((hshs[t][i+len]-hshs[t][i]*pows[len])%MOD+MOD)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*BAS%MOD;
  I n;cin>>n;
  S s;cin>>s;
  I m;cin>>m;
  S t;cin>>t;
  I x;cin>>x;
  for(I i=0;i<n;i++)hshs[0][i+1]=(hshs[0][i]*BAS+s[i])%MOD;
  for(I i=0;i<m;i++)hshs[1][i+1]=(hshs[1][i]*BAS+t[i])%MOD;
  for(I i=0;i<n;i++)for(I j=0;j<=x;j++){
    I pre=dp[i][j];
    if(pre<m&&j+1<=x&&s[i]==t[pre]){
      I l=1,r=min(n-i,m-pre);
      while(l<r){
        I t=l+(r-l+1)/2;
        qry(0,i,t)==qry(1,pre,t)?l=t:r=t-1;
      }
      dp[i+l][j+1]=max(dp[i+l][j+1],pre+l);
    }
    dp[i+1][j]=max(dp[i+1][j],pre);
  }
  printf("%s\n",*max_element(dp[n],dp[n]+x+1)==m?"YES":"NO");
}