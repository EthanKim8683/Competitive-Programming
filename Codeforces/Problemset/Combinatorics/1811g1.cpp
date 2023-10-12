#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=100;
const Lli MOD=1e9+7;
I c_arr[N];
Lli dp[N+1][N+1];
B viss[N+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>c_arr[i];
    for(I i=0;i<=n;i++)for(I j=0;j<=n;j++)dp[i][j]=0,viss[i][j]=0;
    dp[0][0]=1,viss[0][0]=1;
    for(I i=0;i<n;i++)for(I j=i;j>=0;j--){
      I c=c_arr[i];
      if(j%k==0){
        for(I l=0;l<=n;l++)(dp[j+1][c]+=dp[j][l])%=MOD,viss[j+1][c]|=viss[j][l];
      }else{
        (dp[j+1][c]+=dp[j][c])%=MOD,viss[j+1][c]|=viss[j][c];
      }
    }
    Lli res=0;
    for(I i=n/k*k;i>=0;i-=k){
      B vis=0;
      for(I j=0;j<=n;j++)(res+=dp[i][j])%=MOD,vis|=viss[i][j];
      if(vis)break;
    }
    printf("%lli\n",res);
  }
}
/*
we can use dynamic programming on index, length and color
*/