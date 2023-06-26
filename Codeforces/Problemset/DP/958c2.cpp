#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=20000;
const I K=50;
const I P=100;
const I MIN=-1e9;
I a_arr[N];
I dp[N+1][K][P+1];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*K*(P+1),MIN);
  I n,k,p;cin>>n>>k>>p;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0][0]=0;
  for(I i=0;i<n;i++)for(I j=0;j<k;j++)for(I l=0;l<p;l++){
    I a=a_arr[i];
    cmb(dp[i+1][j][(l+a)%p],dp[i][j][l]);
    if(j+1<k)cmb(dp[i+1][j+1][a%p],dp[i][j][l]+l);
  }
  I res=0;
  for(I i=0;i<p;i++)cmb(res,dp[n][k-1][i]+i);
  printf("%i\n",res);
}