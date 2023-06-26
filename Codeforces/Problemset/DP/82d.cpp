#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1000;
const I MAX=1e9;
I a_arr[N];
tuple<I,I,I,I,I>dp[N+1][N+1];
vector<pair<I,I>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(N+1),tuple<I,I,I,I,I>{MAX,-1,-1,-1,-1});
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][n]={0,-1,-1,-1,-1};
  for(I i=0;i<=n;i++){
    for(I j=0;j<i;j++){
      if(i+1<n)dp[i+2][i]=min(dp[i+2][i],{get<0>(dp[i][j])+max(a_arr[i+1],a_arr[j]),i,j,i+1,j});
      if(i+1<n)dp[i+2][i+1]=min(dp[i+2][i+1],{get<0>(dp[i][j])+max(a_arr[i],a_arr[j]),i,j,i,j});
      if(i+1<n)dp[i+2][j]=min(dp[i+2][j],{get<0>(dp[i][j])+max(a_arr[i],a_arr[i+1]),i,j,i,i+1});
      if(i+1==n)dp[i+1][n]=min(dp[i+1][n],{get<0>(dp[i][j])+max(a_arr[i],a_arr[j]),i,j,i,j});
      if(i==n)dp[i][n]=min(dp[i][n],{get<0>(dp[i][j])+a_arr[j],i,j,j,-1});
    }
    if(i+2<n)dp[i+3][i]=min(dp[i+3][i],{get<0>(dp[i][n])+max(a_arr[i+1],a_arr[i+2]),i,n,i+1,i+2});
    if(i+2<n)dp[i+3][i+1]=min(dp[i+3][i+1],{get<0>(dp[i][n])+max(a_arr[i],a_arr[i+2]),i,n,i,i+2});
    if(i+2<n)dp[i+3][i+2]=min(dp[i+3][i+2],{get<0>(dp[i][n])+max(a_arr[i],a_arr[i+1]),i,n,i,i+1});
    if(i+2==n)dp[i+2][n]=min(dp[i+2][n],{get<0>(dp[i][n])+max(a_arr[i],a_arr[i+1]),i,n,i,i+1});
    if(i+1==n)dp[i+1][n]=min(dp[i+1][n],{get<0>(dp[i][n])+a_arr[i],i,n,i,-1});
  }
  I i1=n,j1=n;
  while(i1){
    auto[val,i2,j2,a,b]=dp[i1][j1];
    ress.push_back({a,b});
    tie(i1,j1)=tie(i2,j2);
  }
  reverse(ress.begin(),ress.end());
  printf("%i\n",get<0>(dp[n][n]));
  for(auto[a,b]:ress){
    if(a!=-1)printf("%i ",a+1);
    if(b!=-1)printf("%i ",b+1);
    printf("\n");
  }
}