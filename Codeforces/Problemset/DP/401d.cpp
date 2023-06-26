#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I L=19;
const I M=100;
I cnts[10];
I lows[10];
I sizs[10];
I msks[10];
Lli dp[1<<L][M];
I m;
void dfs(I i,I msk=0){
  if(i==10){
    for(I j=0;j<m;j++)for(I k=msk==0;k<10;k++){
      I cnt=(msk&msks[k])>>lows[k];
      if(cnt>=cnts[k])continue;
      I trn=(msk&~msks[k])|(cnt+1)<<lows[k];
      dp[trn][(j*10+k)%m]+=dp[msk][j];
    }
    return;
  }
  for(I j=0;j<=cnts[i];j++)dfs(i+1,msk|j<<lows[i]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n;cin>>n>>m;
  for(Lli i=n;i;i/=10)cnts[i%10]++;
  for(I i=0;i<10;i++)sizs[i]=cnts[i]?32-__builtin_clz(cnts[i]):1;
  for(I i=0;i+1<10;i++)lows[i+1]=lows[i]+sizs[i];
  for(I i=0;i<10;i++)msks[i]=((1<<sizs[i])-1)<<lows[i];
  dp[0][0]=1;
  dfs(0);
  I msk=0;
  for(I i=0;i<10;i++)msk|=cnts[i]<<lows[i];
  printf("%lli\n",dp[msk][0]);
}