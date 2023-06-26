#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
I t_arr[N];
I inds[N];
I ress[N];
B cmp1(I a,I b){
  I t1=t_arr[a],t2=t_arr[b];
  return t1==t2?a<b:t1>t2;
}
B cmp2(I a,I b){
  I t1=t_arr[a],t2=t_arr[b];
  return t1==t2?a>b:t1>t2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I a,b;cin>>a>>b;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  if(a<b){
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp1);
    fill_n(ress,n,2);
    for(I i=0;i<a;i++)ress[inds[i]]=1;
  }
  if(a>b){
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp2);
    fill_n(ress,n,1);
    for(I i=0;i<b;i++)ress[inds[i]]=2;
  }
  if(a==b){
    fill_n(ress,n,1);
    for(I i=a;i<n;i++)ress[i]=2;
  }
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}