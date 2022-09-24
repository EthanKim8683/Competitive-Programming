#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1.5e5;

I h_arr[N];
I ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=h_arr[i];
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  I res=0;
  for(I i=0;i+k<=n;i++)if(ps[i+k]-ps[i]<ps[res+k]-ps[res])res=i;
  printf("%i\n",res+1);
}