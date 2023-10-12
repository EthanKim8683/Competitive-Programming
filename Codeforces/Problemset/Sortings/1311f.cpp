#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
I x_arr[N];
I v_arr[N];
I inds[N];
vector<I>cpss;
pair<Lli,I>segs[2*N];
pair<Lli,I>cmb(pair<Lli,I>a,pair<Lli,I>b){
  return{a.first+b.first,a.second+b.second};
}
void upd(I i,I val){
  for(i+=cpss.size(),segs[i]=cmb(segs[i],{val,1});i>>=1;)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
pair<Lli,I>qry(I l,I r){
  pair<Lli,I>res={0,0};
  for(l+=cpss.size(),r+=cpss.size();l<r;l>>=1,r>>=1){
    if(l&1)res=cmb(res,segs[l++]);
    if(r&1)res=cmb(res,segs[--r]);
  }
  return res;
}
B cmp(I a,I b){
  return x_arr[a]<x_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<n;i++)cin>>v_arr[i];
  for(I i=0;i<n;i++)cpss.push_back(v_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++)v_arr[i]=lower_bound(cpss.begin(),cpss.end(),v_arr[i])-cpss.begin();
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  Lli res=0;
  for(I i=0;i<n;i++){
    I j=inds[i],x=x_arr[j],v=v_arr[j];
    auto[sum,cnt]=qry(0,v+1);
    res+=(Lli)cnt*x-sum,upd(v,x);
  }
  printf("%lli\n",res);
}