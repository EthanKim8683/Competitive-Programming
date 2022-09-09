#include<iostream>
#include<cstdio>
#include<tuple>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I M=1e5;
const I K=1e5;

tuple<I,I,I>edgs[M];
B spcs[K];
I pars[N];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

B uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return 0;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  spcs[a]|=spcs[b];
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  fill_n(pars,n,-1);
  for(I i=0;i<k;i++){I x;cin>>x,spcs[x-1]=1;}
  for(I i=0;i<m;i++){
    I u,v,w;cin>>u>>v>>w;
    edgs[i]={w,u-1,v-1};
  }
  sort(edgs,edgs+m);
  I res=0;
  for(I i=0;i<m;i++){
    auto[w,u,v]=edgs[i];
    B vld=spcs[fnd(u)]&&spcs[fnd(v)];
    if(uni(u,v)&&vld)res=w;
  }
  for(I i=0;i<k;i++)printf("%i ",res);
  return 0;
}