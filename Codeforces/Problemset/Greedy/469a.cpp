#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100;

I a_arr[N];
I b_arr[N];
I viss[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I p;cin>>p;
  for(I i=0;i<p;i++)cin>>a_arr[i];
  I q;cin>>q;
  for(I i=0;i<q;i++)cin>>b_arr[i];
  for(I i=0;i<p;i++)viss[a_arr[i]-1]=1;
  for(I i=0;i<q;i++)viss[b_arr[i]-1]=1;
  printf("%s\n",accumulate(viss,viss+n,0)==n?"I become the guy.":"Oh, my keyboard!");
}