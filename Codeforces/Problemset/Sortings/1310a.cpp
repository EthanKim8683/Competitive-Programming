#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=200000;
I a_arr[N];
I t_arr[N];
I inds[N];
set<I>rems;
set<I>viss;
B cmp(I a,I b){
  return t_arr[a]>t_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>t_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++)rems.insert(a_arr[i]);
  Lli res=0;
  for(I i=0;i<n;i++){
    I j=inds[i],a=a_arr[j];
    auto it=rems.lower_bound(a);
    I b=*it;
    viss.insert(b);
    if(viss.find(b+1)==viss.end())rems.insert(b+1);
    rems.erase(it);
    res+=(Lli)(b-a)*t_arr[j];
  }
  printf("%lli\n",res);
}