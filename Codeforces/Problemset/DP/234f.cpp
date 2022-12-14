#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=200;
const I A=4e4;
const I MAX=1e9;
I h_arr[N];
I dp[N][A+1][2];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
#ifndef ETHANKIM8683
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+N*(A+1)*2,MAX);
  I n;cin>>n;
  I a,b;cin>>a>>b;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  I h=h_arr[0];
  dp[0][h][0]=dp[0][0][1]=0;
  for(I i=1;i<n;i++)for(I j=0;j<=a;j++){
    I x=h_arr[i-1],y=h_arr[i];
    cmb(dp[i][j+y][0],dp[i-1][j][0]);
    cmb(dp[i][j+y][0],dp[i-1][j][1]+min(x,y));
    cmb(dp[i][j+0][1],dp[i-1][j][0]+min(x,y));
    cmb(dp[i][j+0][1],dp[i-1][j][1]);
  }
  I res=MAX,tot=accumulate(h_arr,h_arr+n,0);
  for(I i=tot-b;i<=a;i++){
    cmb(res,dp[n-1][i][0]);
    cmb(res,dp[n-1][i][1]);
  }
  printf("%i\n",res==MAX?-1:res);
}