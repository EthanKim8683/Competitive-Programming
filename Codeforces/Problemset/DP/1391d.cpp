#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
const I N=1e6;
const I MAX=1e9;
S mats[N];
I msks[N];
I dp[N][1<<3];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*(1<<3),MAX);
  I n,m;cin>>n>>m;
  if(n<=1||m<=1)printf("0"),exit(0);
  if(n>=4&&m>=4)printf("-1"),exit(0);
  for(I i=0;i<n;i++)cin>>mats[i];
  if(m>n){
    swap(n,m);
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)msks[i]|=(mats[j][i]-'0')<<j;
  }else{
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)msks[i]|=(mats[i][j]-'0')<<j;
  }
  I res=MAX;
  if(m==2){
    for(I i=0;i<(1<<2);i++)dp[0][i]=__builtin_popcount(msks[0]^i);
    for(I i=1;i<n;i++)for(I j=0;j<(1<<2);j++)for(I k=0;k<(1<<2);k++)if((__builtin_popcount(j)+__builtin_popcount(k))%2)dp[i][k]=min(dp[i][k],dp[i-1][j]+__builtin_popcount(msks[i]^k));
    for(I i=0;i<(1<<2);i++)res=min(res,dp[n-1][i]);
  }
  if(m==3){
    for(I i=0;i<(1<<3);i++)dp[0][i]=__builtin_popcount(msks[0]^i);
    for(I i=1;i<n;i++)for(I j=0;j<(1<<3);j++)for(I k=0;k<(1<<3);k++)if((__builtin_popcount(j&3)+__builtin_popcount(k&3))%2&&(__builtin_popcount(j&6)+__builtin_popcount(k&6))%2)dp[i][k]=min(dp[i][k],dp[i-1][j]+__builtin_popcount(msks[i]^k));
    for(I i=0;i<(1<<3);i++)res=min(res,dp[n-1][i]);
  }
  printf("%i\n",res);
}