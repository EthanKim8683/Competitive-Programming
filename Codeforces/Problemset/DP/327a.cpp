#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;

I a_arr[N];
I ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]+=a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  I res=0;
  for(I l=0;l<n;l++)for(I r=l;r<n;r++)
    res=max(res,(ps[l]-ps[0])+((r+1-l)-(ps[r+1]-ps[l]))+(ps[n]-ps[r+1]));
  printf("%i\n",res);
}