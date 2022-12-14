#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
const I K=100;
I d_arr[N];
B dp[N+1][2*K];
I n,k,l;
B vld(I i,I j){
  if(i>=n)return 1;
  return d_arr[i]+min(j,2*k-j)<=l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>k>>l;
    for(I i=0;i<n;i++)cin>>d_arr[i];
    for(I i=0;i<=n;i++)for(I j=0;j<2*k;j++)dp[i][j]=0;
    for(I i=0;i<2*k;i++)if(vld(0,i))dp[0][i]=1;
    for(I i=0;i<n;i++){
      for(I j=0;j<2*k;j++){
        I l=(j+1)%(2*k);
        if(vld(i+0,l))dp[i+0][l]|=dp[i][j];
      }
      for(I j=0;j<2*k;j++){
        I l=(j+1)%(2*k);
        if(vld(i+0,l))dp[i+0][l]|=dp[i][j];
      }
      for(I j=0;j<2*k;j++){
        I l=(j+1)%(2*k);
        if(vld(i+1,l))dp[i+1][l]|=dp[i][j];
      }
    }
    printf("%s\n",accumulate(dp[n],dp[n]+2*k,0)?"Yes":"No");
  }
}