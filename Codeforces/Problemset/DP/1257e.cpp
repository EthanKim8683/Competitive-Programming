#include<bits/stdc++.h>
using namespace std;
using I=int;
const I K1=2e5;
const I K2=2e5;
const I K3=2e5;
const I N=2e5;
const I MAX=1e9;
I a1_arr[K1];
I a2_arr[K2];
I a3_arr[K3];
I ps1[N+1],ps2[N+1],ps3[N+1];
I csts[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k1,k2,k3;cin>>k1>>k2>>k3;
  for(I i=0;i<k1;i++)cin>>a1_arr[i];
  for(I i=0;i<k2;i++)cin>>a2_arr[i];
  for(I i=0;i<k3;i++)cin>>a3_arr[i];
  I n=k1+k2+k3;
  for(I i=0;i<k1;i++)ps1[a1_arr[i]]++;
  for(I i=0;i<k2;i++)ps2[a2_arr[i]]++;
  for(I i=0;i<k3;i++)ps3[a3_arr[i]]++;
  for(I i=0;i<n;i++)ps1[i+1]+=ps1[i];
  for(I i=0;i<n;i++)ps2[i+1]+=ps2[i];
  for(I i=0;i<n;i++)ps3[i+1]+=ps3[i];
  for(I i=0;i<=n;i++)csts[i]=ps3[i]-ps2[i];
  for(I i=n;i>0;i--)csts[i-1]=min(csts[i-1],csts[i]);
  I res=MAX;
  for(I i=0;i<=n;i++)res=min(res,ps2[i]-ps2[0]-ps3[0]-ps1[i]+ps1[n]+ps2[n]+csts[i]);
  printf("%i\n",res);
}