#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
const I Q=1e5;
const I A=1e6;
const I S=1e9;
I a_arr[N];
I s_arr[Q];
Lli ps[N+1];
vector<I>unqs;
I qrys[Q];
I inds[Q];
B ress[Q];
B viss[Q];
I n,q;
B cmp(I a,I b){
  return s_arr[a]<s_arr[b];
}
void dfs(I l,I r){
  Lli sum=ps[upper_bound(a_arr,a_arr+n,r)-a_arr]-ps[lower_bound(a_arr,a_arr+n,l)-a_arr];
  I low=lower_bound(qrys,qrys+q,sum)-qrys,upp=upper_bound(qrys,qrys+q,sum)-qrys;
  for(I i=low;i<upp;i++){
    if(viss[i])break;
    viss[i]=1;
    ress[inds[i]]=1;
  }
  auto it=upper_bound(unqs.begin(),unqs.end(),l+(r-l)/2);
  if(it!=unqs.begin()){
    I m=*prev(it);
    if(m!=r)dfs(l,m);
  }
  if(it!=unqs.end()){
    I m=*it;
    if(m!=l)dfs(m,r);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  srand(time(NULL));
  I t;cin>>t;
  while(t--){
    cin>>n>>q;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<q;i++)cin>>s_arr[i];
    sort(a_arr,a_arr+n);
    iota(inds,inds+q,0);
    sort(inds,inds+q,cmp);
    for(I i=0;i<q;i++)qrys[i]=s_arr[inds[i]];
    for(I i=0;i<n;i++)ps[i+1]=ps[i]+a_arr[i];
    unqs.clear();
    for(I i=0;i<n;i++)unqs.push_back(a_arr[i]);
    unqs.erase(unique(unqs.begin(),unqs.end()),unqs.end());
    fill_n(viss,q,0),fill_n(ress,q,0);
    dfs(unqs.front(),unqs.back());
    for(I i=0;i<q;i++)printf("%s\n",ress[i]?"Yes":"No");
  }
}