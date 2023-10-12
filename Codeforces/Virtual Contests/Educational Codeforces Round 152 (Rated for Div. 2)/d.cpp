#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I MAX=1e9;
I a_arr[N];
I dp[N][2][2+1];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+N*2*(2+1),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I a=a_arr[0];
  dp[0][0][a]=0,dp[0][1][a]=1;
  for(I i=0;i+1<n;i++)for(I j=0;j<=2;j++){
    I a=a_arr[i+1];
    if(a-1>=0)cmb(dp[i+1][0][a-1],dp[i][0][j]);
    if(a-1>=0)cmb(dp[i+1][1][a-1],dp[i][0][j]+1);
    if(j-1>=0)cmb(dp[i+1][1][a],dp[i][1][j]);
    if(j-1>=0)cmb(dp[i+1][1][a],dp[i][0][j]+1);
    cmb(dp[i+1][0][a],dp[i][0][j]+1);
    cmb(dp[i+1][1][a],dp[i][0][j]+2);
    cmb(dp[i+1][0][a],dp[i][1][j]);
    cmb(dp[i+1][1][a],dp[i][1][j]+1);
  }
  printf("%i\n",*min_element(dp[n-1][1],dp[n-1][1]+2+1));
}