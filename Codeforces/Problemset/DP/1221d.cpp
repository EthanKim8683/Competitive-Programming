#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=3e5;
const Lli MAX=1e18;

I a_arr[N];
I b_arr[N];
Lli dp[N][3];

void cmb(Lli&a,Lli b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i]>>b_arr[i];
    for(I i=0;i<n;i++)for(I j=0;j<3;j++)dp[i][j]=MAX;
    for(I i=0;i<3;i++)dp[0][i]=b_arr[0]*i;
    for(I i=0;i+1<n;i++)for(I j=0;j<3;j++)for(I k=0;k<3;k++)
      if(a_arr[i]+j!=a_arr[i+1]+k)cmb(dp[i+1][k],dp[i][j]+k*b_arr[i+1]);
    printf("%lli\n",*min_element(dp[n-1],dp[n-1]+3));
  }
}