#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100000;

I a_arr[N];
I cpss[N];

I main(){
#ifndef ETHANKIM8683
  freopen("sort.in","r",stdin);
  freopen("sort.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  copy_n(a_arr,n,cpss);
  sort(cpss,cpss+n);
  for(I i=0;i<n;i++)a_arr[i]=upper_bound(cpss,cpss+n,a_arr[i])-cpss-1;
  I res=1;
  for(I i=0;i<n;i++)res=max(res,i-a_arr[i]+1);
  printf("%i\n",res);
}