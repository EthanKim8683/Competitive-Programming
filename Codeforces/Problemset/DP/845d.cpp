#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I S=300;
const I MAX=1e9;
pair<I,I>eves[N];
I dp[2][S+1][2];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+2*(S+1)*2,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I t;cin>>t;
    I s;
    if(t==1||t==3)cin>>s;
    eves[i]={t,s};
  }
  auto[t,s]=eves[0];
  I cur=s;
  dp[0][S][1]=0;
  for(I i=0;i+1<n;i++)for(I j=0;j<=S;j++)for(I k=0;k<2;k++){
    auto[t,s]=eves[i+1];
    if(t==1){
      cur=s;
      if(j>=cur)cmb(dp[(i+1)%2][j][k],dp[i%2][j][k]);
    }
    if(t==2){
      if(k==1)cmb(dp[(i+1)%2][j][k],dp[i%2][j][k]);
    }
    if(t==3){
      if(s>=cur)cmb(dp[(i+1)%2][s][k],dp[i%2][j][k]);
      cmb(dp[(i+1)%2][j][k],dp[i%2][j][k]+1);
    }
    if(t==4){
      cmb(dp[(i+1)%2][j][1],dp[i%2][j][k]);
      cmb(dp[(i+1)%2][j][k],dp[i%2][j][k]+1);
    }
    if(t==5){
      cmb(dp[(i+1)%2][S][k],dp[i%2][j][k]);
      cmb(dp[(i+1)%2][j][k],dp[i%2][j][k]+1);
    }
    if(t==6){
      cmb(dp[(i+1)%2][j][0],dp[i%2][j][k]);
      cmb(dp[(i+1)%2][j][k],dp[i%2][j][k]+1);
    }
    dp[i%2][j][k]=MAX;
  }
  I res=MAX;
  for(I i=0;i<=S;i++)for(I j=0;j<2;j++)cmb(res,dp[(n-1)%2][i][j]);
  printf("%i\n",res);
}