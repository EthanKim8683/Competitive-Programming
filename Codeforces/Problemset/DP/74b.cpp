#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using S=string;

const I N=50;
const I X=200;

B dp[X+1][N];
I poss[X+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k,m--,k--;
  S s;cin>>s>>s;
  S t;cin>>t;
  I x=t.size();
  I d;
  if(s=="tail")d=1;
  if(s=="head")d=-1;
  poss[0]=k;
  for(I i=1;i<=x;i++){
    if(k==0)d=1;
    if(k==n-1)d=-1;
    poss[i]=(k+=d);
  }
  dp[0][m]=1;
  for(I i=0;i<x;i++){
    if(t[i]=='0'){
      for(I j=0;j<n;j++){
        if(j-1>=0&&poss[i]!=j-1&&poss[i+1]!=j-1)dp[i+1][j-1]|=dp[i][j];
        if(j+1<n&&poss[i]!=j+1&&poss[i+1]!=j+1)dp[i+1][j+1]|=dp[i][j];
        if(poss[i+1]!=j)dp[i+1][j]|=dp[i][j];
      }
    }
    if(t[i]=='1'){
      for(I j=0;j<n;j++)for(I k=0;k<n;k++)
        if(poss[i+1]!=k)dp[i+1][k]|=dp[i][j];
    }
  }
  B res=0;
  for(I i=0;i<n;i++)res|=dp[x][i];
  if(res)printf("Stowaway\n"),exit(0);
  I lst=0;
  for(I i=0;i<x;i++)if(accumulate(dp[i],dp[i]+n,0))lst=i+1;
  printf("Controller %i\n",lst);
}