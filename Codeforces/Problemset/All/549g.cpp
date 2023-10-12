#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=200000;
I a_arr[N];
I inds[N];
I ress[N];
B cmp(I a,I b){
  return a_arr[a]+a<a_arr[b]+b;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++){
    I j=inds[i];
    ress[i]=a_arr[j]+j-i;
    if(i-1>=0&&ress[i]<ress[i-1])printf(":("),exit(0);
  }
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}