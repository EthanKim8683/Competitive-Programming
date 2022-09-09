#include<iostream>
#include<cstdio>
#include<vector>
#include<numeric>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=200000;

I pars[N];
I mins[N],maxs[N];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

B uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return false;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  mins[a]=min(mins[a],mins[b]);
  maxs[a]=max(maxs[a],maxs[b]);
  return true;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  iota(mins,mins+n,0),iota(maxs,maxs+n,0);
  for(I i=0;i<m;i++){I u,v;cin>>u>>v,uni(u-1,v-1);}
  I res=0,j=0;
  for(I i=0;i<n;i++)
    for(j=max(j,mins[fnd(i)]+1);j<maxs[fnd(i)];j++)
      res+=uni(i,j);
  printf("%i\n",res);
  return 0;
}