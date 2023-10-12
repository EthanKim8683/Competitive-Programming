#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=4e5;
const I A=20;
const Lli MAX=1e18;
I a_arr[N];
I pres[A];
Lli csts[A][A];
Lli dp[1<<A];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I a=a_arr[i]-1;
    for(I j=0;j<A;j++)if(j!=a)csts[a][j]+=pres[j];
    pres[a]++;
  }
  fill_n(dp,1<<A,MAX),dp[0]=0;
  for(I i=0;i<(1<<A);i++)for(I j=0;j<A;j++)if(~i>>j&1){
    Lli tot=dp[i];
    for(I k=0;k<A;k++)if(~i>>k&1)tot+=csts[j][k];
    dp[i|1<<j]=min(dp[i|1<<j],tot);
  }
  printf("%lli\n",dp[(1<<A)-1]);
}