#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=18;
Lf a_arr[N][N];
Lf dp[1<<N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)cin>>a_arr[i][j];
  dp[(1<<n)-1]=1;
  for(I i=(1<<n)-1;i>=0;i--){
    I cnt=__builtin_popcount(i),tot=cnt*(cnt-1)/2;
    for(I j=0;j<n;j++)if(i>>j&1){
      for(I k=j+1;k<n;k++)if(i>>k&1){
        dp[i^(1<<j)]+=dp[i]*a_arr[k][j]/tot;
        dp[i^(1<<k)]+=dp[i]*a_arr[j][k]/tot;
      }
    }
  }
  for(I i=0;i<n;i++)printf("%.6Lf ",dp[1<<i]);
}