#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I R=200;
const I G=200;
const I B=200;
const Lli MIN=-1e18;

I r_arr[R];
I g_arr[G];
I b_arr[B];
Lli dp[R+1][G+1][B+1];

void cmb(Lli&a,Lli b){
  a=max(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(R+1)*(G+1)*(B+1),MIN);
  I r,g,b;cin>>r>>g>>b;
  for(I i=0;i<r;i++)cin>>r_arr[i];
  for(I i=0;i<g;i++)cin>>g_arr[i];
  for(I i=0;i<b;i++)cin>>b_arr[i];
  sort(r_arr,r_arr+r,greater<I>());
  sort(g_arr,g_arr+g,greater<I>());
  sort(b_arr,b_arr+b,greater<I>());
  dp[0][0][0]=0;
  for(I i=0;i<=r;i++)for(I j=0;j<=g;j++)for(I k=0;k<=b;k++){
    if(dp[i][j][k]==MIN)continue;
    if(i<r&&j<g)cmb(dp[i+1][j+1][k],dp[i][j][k]+r_arr[i]*g_arr[j]);
    if(i<r&&k<b)cmb(dp[i+1][j][k+1],dp[i][j][k]+r_arr[i]*b_arr[k]);
    if(j<g&&k<b)cmb(dp[i][j+1][k+1],dp[i][j][k]+g_arr[j]*b_arr[k]);
    if(i+1<=r)cmb(dp[i+1][j][k],dp[i][j][k]);
    if(j+1<=g)cmb(dp[i][j+1][k],dp[i][j][k]);
    if(k+1<=b)cmb(dp[i][j][k+1],dp[i][j][k]);
  }
  printf("%lli\n",dp[r][g][b]);
}