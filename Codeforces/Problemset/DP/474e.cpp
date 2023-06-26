#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I MIN=-1e9;
Lli h_arr[N];
vector<Lli>cpss;
pair<I,I>segs[2*N];
I pars[N];
vector<I>ress;
void upd(I i,pair<I,I>val){
  i+=cpss.size();
  for(segs[i]=max(segs[i],val);i>>=1;)segs[i]=max(segs[i<<1],segs[i<<1|1]);
}
pair<I,I>qry(I l,I r){
  pair<I,I>res={0,-1};
  for(l+=cpss.size(),r+=cpss.size();l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs[l++]);
    if(r&1)res=max(res,segs[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,d;cin>>n>>d;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  for(I i=0;i<n;i++)cpss.push_back(h_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  fill_n(segs,2*cpss.size(),pair<I,I>{MIN,-1});
  for(I i=0;i<n;i++){
    I low=upper_bound(cpss.begin(),cpss.end(),h_arr[i]-d)-cpss.begin();
    I upp=lower_bound(cpss.begin(),cpss.end(),h_arr[i]+d)-cpss.begin();
    auto[len,p]=max(qry(0,low),qry(upp,cpss.size()));
    upd(lower_bound(cpss.begin(),cpss.end(),h_arr[i])-cpss.begin(),{len+1,i});
    pars[i]=p;
  }
  auto[len,i]=qry(0,cpss.size());
  for(;i!=-1;i=pars[i])ress.push_back(i);
  reverse(ress.begin(),ress.end());
  printf("%i\n",len);
  for(auto i:ress)printf("%i ",i+1);
}