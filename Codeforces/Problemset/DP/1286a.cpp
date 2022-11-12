#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100;
const I MAX=1e9;

I p_arr[N];
I dp[N+1][N+1][2];

void cmb(I&a,I b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(N+1)*2,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  I eve=n/2,odd=n/2+n%2;
  dp[0][0][0]=dp[0][0][1]=0;
  for(I i=0;i<=eve;i++)for(I j=0;j<=odd;j++)for(I k=0;k<2;k++){
    if(i+j>=n)continue;
    I p=p_arr[i+j];
    if(p){
      if(p%2==0&&i+1<=eve)cmb(dp[i+1][j][0],dp[i][j][k]+(k!=0));
      if(p%2==1&&j+1<=odd)cmb(dp[i][j+1][1],dp[i][j][k]+(k!=1));
    }else{
      if(i+1<=eve)cmb(dp[i+1][j][0],dp[i][j][k]+(k!=0));
      if(j+1<=odd)cmb(dp[i][j+1][1],dp[i][j][k]+(k!=1));
    }
  }
  printf("%i\n",min(dp[eve][odd][0],dp[eve][odd][1]));
}