#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
I a_arr[N];
I inds[N];
I ress[N];
set<I>rems;
B cmp(I a,I b){
  return a_arr[a]>a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++)rems.insert(i);
  for(I i=0,t=0;i<n;i++){
    I j=inds[i];
    if(rems.find(j)==rems.end())continue;
    for(I l=0;l<k;l++){
      auto it=rems.find(j);
      if(it--==rems.begin())break;
      ress[*it]=t,rems.erase(it);
    }
    for(I l=0;l<k;l++){
      auto it=rems.find(j);
      if(++it==rems.end())break;
      ress[*it]=t,rems.erase(it);
    }
    ress[j]=t,rems.erase(j);
    t=!t;
  }
  for(I i=0;i<n;i++)printf("%i",ress[i]+1);
}