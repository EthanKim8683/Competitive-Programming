#include<iostream>
#include<cstdio>
#include<set>
#include<tuple>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I E=1e9;

set<tuple<I,I,I,I>>edgs;
I pars[N];
I n;
I a1,b1;

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

B chk(I x){
  edgs.insert({x,0,a1,b1});
  fill_n(pars,n,-1);
  B res=0;
  for(auto[w,i,a,b]:edgs){
    res=uni(a,b);
    if(!i)break;
  }
  edgs.erase({x,0,a1,b1});
  return res;
}

I fnd(){
  I l=0,r=E;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(m))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  I e;cin>>a1>>b1>>e,a1--,b1--;
  for(I i=1;i<m;i++){
    I a,b,e;cin>>a>>b>>e;
    edgs.insert({e,i,a-1,b-1});
  }
  printf("%i\n",fnd());
  return 0;
}