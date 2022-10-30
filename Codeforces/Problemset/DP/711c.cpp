#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=100;
const I M=100;
const I K=100;
const Lli MAX=1e18;

I c_arr[N];
Lli csts[N][M+1];
Lli dp[N+1][K+1][M+1];

void cmb(Lli&a,Lli b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(K+1)*(M+1),MAX);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  for(I i=0;i<n;i++)for(I j=1;j<=m;j++)cin>>csts[i][j];
  dp[0][0][0]=0;
  for(I i=0;i<n;i++)for(I j=0;j<=k;j++)for(I l=0;l<=m;l++){
    if(dp[i][j][l]==MAX)continue;
    I c=c_arr[i];
    if(c==0)for(I o=1;o<=m;o++)cmb(dp[i+1][j+(o!=l)][o],dp[i][j][l]+csts[i][o]);
    else cmb(dp[i+1][j+(c!=l)][c],dp[i][j][l]);
  }
  Lli res=*min_element(dp[n][k]+1,dp[n][k]+m+1);
  printf("%lli\n",res==MAX?-1:res);
}