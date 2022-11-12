#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;

I c_arr[N];

I main(){
#ifndef ETHANKIM8683
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n,x;cin>>n>>x;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  for(I i=0;i<n;i++)c_arr[i]*=n-i;
  sort(c_arr,c_arr+n);
  I res=0;
  for(I i=0;i<n&&c_arr[i]<=x;i++)x-=c_arr[i],res++;
  printf("%i\n",res);
}