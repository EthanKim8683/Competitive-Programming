#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=18;

I a_arr[N];
Lli dp[1<<N][N];
Lli pres[N][N];

void cmb(Lli&a,Lli b){
  a=max(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<k;i++){
    I x,y,c;cin>>x>>y>>c;
    pres[y-1][x-1]=c;
  }
  for(I i=0;i<n;i++)dp[1<<i][i]=a_arr[i];
  for(I i=1;i<(1<<n);i++)for(I j=0;j<n;j++)if(i>>j&1){
    for(I k=0;k<n;k++){
      if(i>>k&1)continue;
      cmb(dp[i|1<<k][k],dp[i][j]+pres[k][j]+a_arr[k]);
    }
  }
  Lli res=0;
  for(I i=0;i<(1<<n);i++){
    if(__builtin_popcount(i)!=m)continue;
    cmb(res,*max_element(dp[i],dp[i]+n));
  }
  printf("%lli\n",res);
}