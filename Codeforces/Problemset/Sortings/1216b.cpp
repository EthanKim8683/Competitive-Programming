#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1000;
I a_arr[N];
I inds[N];
B cmp(I a,I b){
  return a_arr[a]>a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  I res=0;
  for(I i=0;i<n;i++)res+=i*a_arr[inds[i]]+1;
  printf("%i\n",res);
  for(I i=0;i<n;i++)printf("%i ",inds[i]+1);
}