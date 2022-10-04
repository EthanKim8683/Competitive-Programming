#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const I M=2e5;

Lli ps[N+1];
Lli a_arr[N];
Lli b_arr[M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=a_arr[i];
  for(I i=0;i<n;i++)ps[i+1]+=ps[i];
  while(m--){
    Lli b;cin>>b,b--;
    Lli drm=upper_bound(ps,ps+n,b)-ps-1;
    Lli rom=b-ps[drm];
    printf("%lli %lli\n",drm+1,rom+1);
  }
}