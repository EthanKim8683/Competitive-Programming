#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=500;
const I K=10;
const I C=1e5;
I c_arr[N*K];
I f_arr[N];
I h_arr[K];
I sups[C+1];
I dems[C+1];
Lli dp[N*K+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n*k;i++)cin>>c_arr[i];
  for(I i=0;i<n;i++)cin>>f_arr[i];
  for(I i=0;i<k;i++)cin>>h_arr[i];
  for(I i=0;i<n*k;i++)sups[c_arr[i]]++;
  for(I i=0;i<n;i++)dems[f_arr[i]]++;
  Lli res=0;
  for(I i=1;i<=C;i++){
    I sup=sups[i],dem=dems[i];
    for(I x=0;x<=sup;x++)for(I y=0;y<=dem;y++)dp[x][y]=0;
    for(I x=0;x<sup;x++)for(I y=0;y<=dem;y++){
      if(y+1<=dem)for(I z=0;z<k;z++)if(x+z+1<=sup)dp[x+z+1][y+1]=max(dp[x+z+1][y+1],dp[x][y]+h_arr[z]);
      dp[x+1][y]=max(dp[x+1][y],dp[x][y]);
    }
    res+=*max_element(dp[sup],dp[sup]+dem+1);
  }
  printf("%lli\n",res);
}