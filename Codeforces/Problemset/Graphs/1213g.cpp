#include<iostream>
#include<cstdio>
#include<tuple>
#include<algorithm>
#include<map>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I pars[N];
tuple<I,I,I>edgs[N-1];
map<I,Lli>ress;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I siz(I i){
  return -pars[fnd(i)];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  for(I i=0;i<n-1;i++){
    I u,v,w;cin>>u>>v>>w;
    edgs[i]={w,u-1,v-1};
  }
  sort(edgs,edgs+n-1);
  Lli cur=0;
  for(I i=0;i<n-1;i++){
    auto[w,u,v]=edgs[i];
    cur+=(Lli)siz(u)*siz(v);
    uni(u,v);
    ress[w]=cur;
  }
  for(I i=0;i<m;i++){
    I q;cin>>q;
    auto it=ress.upper_bound(q);
    if(it==ress.begin())printf("0 ");
    else printf("%lli ",prev(it)->second);
  }
  return 0;
}