#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=500;
const I MAX=1e9;

I dp[N][N];
I c_arr[N];

void cmb(I& a,I b){
  a=min(a,b);
}

I main(){
  fill(&dp[0][0],&dp[0][0]+sizeof(dp)/sizeof(I),MAX);
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  for(I i=n-1;i>=0;i--){
    dp[i][i]=1;
    if(i+1<n)dp[i][i+1]=c_arr[i]==c_arr[i+1]?1:2;
    for(I j=i+2;j<n;j++){
      if(c_arr[i]==c_arr[j])cmb(dp[i][j],dp[i+1][j-1]);
      for(I k=i;k<j;k++)cmb(dp[i][j],dp[i][k]+dp[k+1][j]);
    }
  }
  printf("%i\n",dp[0][n-1]);
  return 0;
}