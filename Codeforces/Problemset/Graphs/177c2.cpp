#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I pars[N];
B invs[N];
vector<I>rots;

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
  I n;cin>>n;
  fill_n(pars,n,-1);
  I k;cin>>k;
  for(I i=0;i<k;i++){
    I u,v;cin>>u>>v;
    uni(u-1,v-1);
  }
  I m;cin>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v;
    u=fnd(u-1),v=fnd(v-1);
    if(u==v)invs[u]=true;
  }
  I res=0;
  for(I i=0;i<n;i++)
    if(fnd(i)==i&&!invs[i])
      res=max(res,siz(i));
  printf("%i\n",res);
  return 0;
}