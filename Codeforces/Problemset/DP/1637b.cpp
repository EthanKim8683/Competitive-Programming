#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=100;

I a_arr[N];
B viss[N+1];
I mexs[N][N];
Lli dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I l=0;l<n;l++)for(I r=l;r<n;r++){
      fill_n(viss,r-l+1+1,0);
      for(I i=l;i<=r;i++)if(a_arr[i]<=r-l+1)viss[a_arr[i]]=1;
      for(I i=0;i<=r-l+1;i++)if(!viss[i]){mexs[l][r]=i;break;}
    }
    Lli res=0;
    for(I i=0;i<n;i++){
      fill(dp+i,dp+n+1,0);
      for(I l=i;l<n;l++)for(I r=l;r<n;r++)dp[r+1]=max(dp[r+1],dp[l]+mexs[l][r]+1);
      for(I j=i+1;j<=n;j++)res+=dp[j];
    }
    printf("%lli\n",res);
  }
}