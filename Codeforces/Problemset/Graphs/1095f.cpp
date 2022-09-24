#include<iostream>
#include<cstdio>
#include<tuple>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=2e5;
const I M=2e5;
const Lli MAX=1e18;

Lli a_arr[N];
tuple<Lli,I,I>edgs[M+N];
I pars[N];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

B uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return 0;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  I ri;
  Lli ra=MAX;
  for(I i=0;i<n;i++){
    Lli a;cin>>a;
    if(a<ra)ri=i,ra=a;
    a_arr[i]=a;
  }
  for(I i=0;i<m;i++){
    I x,y;Lli w;cin>>x>>y>>w;
    edgs[i]={w,x-1,y-1};
  }
  for(I i=0;i<n;i++)
    edgs[m+i]={a_arr[i]+ra,i,ri};
  sort(edgs,edgs+m+n);
  Lli res=0;
  for(I i=0;i<m+n;i++){
    auto[w,x,y]=edgs[i];
    if(uni(x,y))res+=w;
  }
  printf("%lli\n",res);
  return 0;
}