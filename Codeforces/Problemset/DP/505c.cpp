#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=30000;
const I M=30000;
const I MAX=1e9;
const I MIN=-1e9;
I p_arr[N];
I gems[M+1];
I lows[M+1],upps[M+1];
vector<I>dp[M+1];
void add(I i,I j,I val){
  if(j<=0)return;
  i+=j;
  if(i>M)return;
  val+=gems[i];
  j-=lows[i];
  dp[i][j]=max(dp[i][j],val);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(lows,M+1,MAX);
  fill_n(upps,M+1,MIN);
  I n,d;cin>>n>>d;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  for(I i=0;i<n;i++)gems[p_arr[i]]++;
  lows[d]=upps[d]=d;
  for(I i=0;i<=M;i++){
    for(I j=lows[i];j<=upps[i];j++){
      if(i+j-1<=M&&j-1>0){
        lows[i+j-1]=min(lows[i+j-1],j-1);
        upps[i+j-1]=max(upps[i+j-1],j-1);
      }
      if(i+j+1<=M&&j+1>0){
        lows[i+j+1]=min(lows[i+j+1],j+1);
        upps[i+j+1]=max(upps[i+j+1],j+1);
      }
      if(i+j<=M&&j>0){
        lows[i+j]=min(lows[i+j],j);
        upps[i+j]=max(upps[i+j],j);
      }
    }
  }
  for(I i=0;i<=M;i++){
    I siz=upps[i]-lows[i]+1;
    if(siz<=0)continue;
    dp[i].resize(siz);
  }
  I res=0;
  add(0,d,0);
  for(I i=0;i<=M;i++){
    for(I j=lows[i],k=0;j<=upps[i];j++,k++){
      res=max(res,dp[i][k]);
      add(i,j-1,dp[i][k]);
      add(i,j,dp[i][k]);
      add(i,j+1,dp[i][k]);
    }
  }
  printf("%i\n",res);
}