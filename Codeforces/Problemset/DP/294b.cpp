#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100;
const I MAX=1e9;

pair<I,I>boos[N];
B dp[N+1][2*N+1][2*N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I t,w;cin>>t>>w;
    boos[i]={t,w};
  }
  dp[0][0][0]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=2*n;j++)for(I k=0;k<=2*n;k++){
    if(!dp[i][j][k])continue;
    auto[t,w]=boos[i];
    if(j+t<=2*n)dp[i+1][j+t][k]=1;
    if(k+w<=2*n)dp[i+1][j][k+w]=1;
  }
  I res=MAX;
  for(I i=2*n;i>=0;i--){
    B vld=0;
    for(I j=0;j<=i;j++)vld|=dp[n][i][j];
    if(vld)res=i;
  }
  printf("%i\n",res);
}