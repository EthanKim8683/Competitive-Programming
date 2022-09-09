#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=100;
const I MAX=1e9;

I a_arr[N];
I dp[N+1][2][2];

void cmb(I&a,I b){
  a=min(a,b);
}

I main(){
  fill(&dp[0][0][0],&dp[0][0][0]+sizeof(dp)/sizeof(I),MAX);
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0][0]=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    for(I j=0;j<2;j++)for(I k=0;k<2;k++){
      if(a==0)cmb(dp[i+1][0][0],dp[i][j][k]+1);
      if(a==1){
        if(k+1<2)cmb(dp[i+1][0][k+1],dp[i][j][k]);
        cmb(dp[i+1][0][0],dp[i][j][k]+1);
      }
      if(a==2){
        if(j+1<2)cmb(dp[i+1][j+1][0],dp[i][j][k]);
        cmb(dp[i+1][0][0],dp[i][j][k]+1);
      }
      if(a==3){
        if(j+1<2)cmb(dp[i+1][j+1][0],dp[i][j][k]);
        if(k+1<2)cmb(dp[i+1][0][k+1],dp[i][j][k]);
        cmb(dp[i+1][0][0],dp[i][j][k]+1);
      }
    }
  }
  I res=MAX;
  for(I i=0;i<2;i++)for(I j=0;j<2;j++)
    res=min(res,dp[n][i][j]);
  printf("%i\n",res);
  return 0;
}