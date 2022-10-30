#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=5000;

I a_arr[N];
I b_arr[N];
Lli dp[N][N];
Lli ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i+0<n;i++)dp[i][i+0]=(Lli)a_arr[i+0]*b_arr[i+0];
  for(I i=0;i+1<n;i++)dp[i][i+1]=(Lli)a_arr[i+0]*b_arr[i+1]+(Lli)a_arr[i+1]*b_arr[i+0];
  for(I i=2;i<n;i++)for(I j=0;j+i<n;j++)dp[j][j+i]=dp[j+1][j+i-1]+(Lli)a_arr[j]*b_arr[j+i]+(Lli)a_arr[j+i]*b_arr[j];
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+(Lli)a_arr[i]*b_arr[i];
  Lli res=ps[n]-ps[0];
  for(I i=0;i<n;i++)for(I j=i;j<n;j++)res=max(res,ps[n]-ps[j+1]+ps[i]-ps[0]+dp[i][j]);
  printf("%lli\n",res);
}