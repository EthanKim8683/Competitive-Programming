#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=5000;
const I M=5000;

I dp[N+1][M+1];

void cmb(I&a,I b){
  a=max(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  S a;cin>>a;
  S b;cin>>b;
  for(I i=0;i<=n;i++)for(I j=0;j<=m;j++){
    if(i+1<=n)cmb(dp[i+1][j],dp[i][j]-1);
    if(j+1<=m)cmb(dp[i][j+1],dp[i][j]-1);
    if(i<n&&j<m&&a[i]==b[j])cmb(dp[i+1][j+1],dp[i][j]+2);
  }
  I res=0;
  for(I i=0;i<=n;i++)for(I j=0;j<=m;j++)cmb(res,dp[i][j]);
  printf("%i\n",res);
}