#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;

I h_arr[N];
I csts[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,a,b,k;cin>>n>>a>>b>>k;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  for(I i=0;i<n;i++){
    I rem=(h_arr[i]-1)%(a+b)+1;
    csts[i]=rem/a+!!(rem%a)-1;
  }
  sort(csts,csts+n);
  I res=0;
  for(I i=0;i<n;i++)if(k-csts[i]>=0)k-=csts[i],res++;
  printf("%i\n",res);
}