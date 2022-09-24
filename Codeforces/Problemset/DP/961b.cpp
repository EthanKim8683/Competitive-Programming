#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

I a_arr[N];
I t_arr[N];
I ps1[N+1],ps2[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>t_arr[i];
  for(I i=0;i<n;i++)ps1[i+1]=a_arr[i];
  for(I i=0;i<n;i++)ps2[i+1]=a_arr[i]*t_arr[i];
  for(I i=0;i<n;i++)ps1[i+1]+=ps1[i];
  for(I i=0;i<n;i++)ps2[i+1]+=ps2[i];
  I res=0;
  for(I i=0;i+k<=n;i++)
    res=max(res,ps2[i]-ps2[0]+ps1[i+k]-ps1[i]+ps2[n]-ps2[i+k]);
  printf("%i\n",res);
}