#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I MAX=1e9;
I a_arr[N];
I dp[N+1][N+1];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(N+1),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0]=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i],b=min(a,n);
    for(I j=0;j<=n;j++)cmb(dp[i+1][j],dp[i][j]);
    for(I j=0;j+1<=n;j++)cmb(dp[i+1][j+1],dp[i+1][j]+1);
    for(I j=n;j-1>=0;j--)cmb(dp[i+1][j-1],dp[i+1][j]);
    for(I j=0;j<=b;j++)dp[i+1][j]+=j<a;
    for(I j=b+1;j<=n;j++)dp[i+1][j]=MAX;
  }
  I res=MAX;
  for(I i=0;i<=n;i++)cmb(res,dp[n][i]);
  printf("%i\n",res);
}