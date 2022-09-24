#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

I v_arr[N];
I u_arr[N];
Lli ps1[N+1];
Lli ps2[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>v_arr[i];
  copy_n(v_arr,n,u_arr);
  sort(u_arr,u_arr+n);
  for(I i=0;i<n;i++)ps1[i+1]=v_arr[i];
  for(I i=0;i<n;i++)ps2[i+1]=u_arr[i];
  for(I i=0;i<n;i++)ps1[i+1]+=ps1[i];
  for(I i=0;i<n;i++)ps2[i+1]+=ps2[i];
  I m;cin>>m;
  while(m--){
    I t,l,r;cin>>t>>l>>r;
    if(t==1)printf("%lli\n",ps1[r]-ps1[l-1]);
    if(t==2)printf("%lli\n",ps2[r]-ps2[l-1]);
  }
}