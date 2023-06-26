#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
const I A=100;
const I MAX=1e9;
I a_arr[N];
I b_arr[N];
pair<I,I>dp[N+1][2*N*A+1];
void cmb(pair<I,I>&a,pair<I,I>b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(2*N*A+1),pair<I,I>{MAX,MAX});
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  dp[0][N*A]={0,0};
  for(I i=0;i<n;i++)for(I j=-i*A;j<=i*A;j++){
    if(dp[i][N*A+j].first==MAX)continue;
    auto[k,t]=dp[i][N*A+j];
    I a=a_arr[i],b=b_arr[i];
    if(j+a<=N*A)cmb(dp[i+1][N*A+j+a],{k,t+a});
    if(j+a-b>=-N*A)cmb(dp[i+1][N*A+j+a-b],{k+1,t});
  }
  pair<I,I>res={MAX,MAX};
  for(I i=-n*A;i<=0;i++)if(dp[n][N*A+i].first!=MAX)res=min(res,dp[n][N*A+i]);
  auto[k,t]=res;
  printf("%i %i\n",k,t);
}