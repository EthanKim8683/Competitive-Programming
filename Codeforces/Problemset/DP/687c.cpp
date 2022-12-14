#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=500;
const I K=500;
I c_arr[N];
B dp[N+1][K+1][K+1];
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  dp[0][0][0]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=k;j++)for(I l=0;l<=k;l++){
    I c=c_arr[i];
    if(j+c<=k&&l+0<=k)dp[i+1][j+c][l+0]|=dp[i][j][l];
    if(j+c<=k&&l+c<=k)dp[i+1][j+c][l+c]|=dp[i][j][l];
    if(j+0<=k&&l+0<=k)dp[i+1][j+0][l+0]|=dp[i][j][l];
  }
  for(I i=0;i<=k;i++)if(dp[n][k][i])ress.push_back(i);
  printf("%i\n",ress.size());
  for(auto res:ress)printf("%i ",res);
}