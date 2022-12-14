#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
const I MIN=-1e9;
I a_arr[N];
I dp[N][N+1];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)for(I j=0;j<=n;j++)dp[i][j]=MIN;
    dp[0][a_arr[n-1]-1]=0;
    for(I i=0;i<n;i++)for(I j=0;j<=n;j++){
      I a=a_arr[i]-1;
      if(a==j)cmb(dp[i+1][a],dp[i][j]);
      else cmb(dp[i+1][a],dp[i][j]+1),cmb(dp[i+1][j],dp[i][j]+1);
    }
    printf("%i\n",*max_element(dp[n],dp[n]+n+1));
  }
}