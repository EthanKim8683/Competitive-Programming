#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I MIN=-2e9;
I a_arr[N];
I p_arr[N];
I inds[N];
I ress[N];
B cmp(I a,I b){
  return p_arr[a]<p_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,l,r;cin>>n>>l>>r;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>p_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  I low=MIN;
  for(I i=0;i<n;i++){
    I j=inds[i],a=a_arr[j],b=max(low+a+1,l);
    if(b<l||b>r)printf("-1"),exit(0);
    ress[j]=b,low=max(low,b-a);
  }
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}