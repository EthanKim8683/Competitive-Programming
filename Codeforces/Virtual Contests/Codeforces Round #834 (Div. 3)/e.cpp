#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I G=2;
const I B=1;
const Lli MIN=-1e18;
I a_arr[N];
Lli dp[N+1][G+1][B+1];
void cmb(Lli&a,Lli b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,h;cin>>n>>h;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<=n;i++)for(I j=0;j<=G;j++)for(I k=0;k<=B;k++)dp[i][j][k]=MIN;
    sort(a_arr,a_arr+n);
    dp[0][0][0]=h;
    for(I i=0;i<n;i++)for(I j=0;j<=G;j++)for(I k=0;k<=B;k++){
      Lli a=a_arr[i];
      if(j+1<=G)cmb(dp[i][j+1][k],dp[i][j][k]*2);
      if(k+1<=B)cmb(dp[i][j][k+1],dp[i][j][k]*3);
      if(a<dp[i][j][k])cmb(dp[i+1][j][k],dp[i][j][k]+a/2);
    }
    I res=0;
    for(I i=0;i<=n;i++)for(I j=0;j<=G;j++)for(I k=0;k<=B;k++)if(dp[i][j][k]!=MIN)res=i;
    printf("%i\n",res);
  }
}