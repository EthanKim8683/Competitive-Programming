#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
I a_arr[N];
Lli dp[N+1][3];
void cmb(Lli&a,Lli b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli x;cin>>n>>x;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    Lli a=a_arr[i];
    cmb(dp[i+1][0],dp[i][0]+a);
    cmb(dp[i+1][1],dp[i][0]+a*x);
    cmb(dp[i+1][1],dp[i][1]+a*x);
    cmb(dp[i+1][2],dp[i][1]+a);
    cmb(dp[i+1][2],dp[i][2]+a);
  }
  Lli res=0;
  for(I i=0;i<=n;i++)for(I j=0;j<3;j++)cmb(res,dp[i][j]);
  printf("%lli\n",res);
}