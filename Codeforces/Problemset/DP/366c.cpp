#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
const I K=10;
const I B=100;
const I X=N*K*B;
I a_arr[N];
I b_arr[N];
I dp[N+1][X+X+1];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(X+X+1),-1);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  dp[0][X]=0;
  for(I i=0;i<n;i++)for(I j=-X;j<=X;j++){
    if(dp[i][X+j]==-1)continue;
    I a=a_arr[i],b=b_arr[i],x=a-k*b;
    if(j+x>=-X&&j+x<=X)cmb(dp[i+1][X+j+x],dp[i][X+j]+a);
    if(j+0>=-X&&j+0<=X)cmb(dp[i+1][X+j+0],dp[i][X+j]+0);
  }
  I res=dp[n][X];
  printf("%i\n",res?res:-1);
}