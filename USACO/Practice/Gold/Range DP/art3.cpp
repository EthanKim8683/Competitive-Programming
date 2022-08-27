#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=300;
const I MAX=1e9;

I cols[N];
I dp[N][N];

void cmb(I& a,I b){
  a=min(a,b);
}

I main(){
  fill(&dp[0][0],&dp[0][0]+sizeof(dp)/sizeof(I),MAX);
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>cols[i];
  for(I i=n-1;i>=0;i--){
    dp[i][i]=1;
    for(I j=i+1;j<n;j++){
      cmb(dp[i][j],dp[i][j-1]+(cols[j]!=cols[j-1]));
      cmb(dp[i][j],dp[i+1][j]+(cols[i]!=cols[i+1]));
      cmb(dp[i][j],dp[i][j-1]+(cols[i]!=cols[j]));
      cmb(dp[i][j],dp[i+1][j]+(cols[i]!=cols[j]));
      for(I k=i;k<j;k++)cmb(dp[i][j],dp[i][k]+dp[k+1][j]);
    }
  }
  printf("%i\n",dp[0][n-1]);
  return 0;
}