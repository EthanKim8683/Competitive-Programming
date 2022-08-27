#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1000;

I pars1[N],pars2[N];
vector<pair<I,I>>ress;

I fnd(I pars[],I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars,pars[i]);
}

void uni(I pars[],I a,I b){
  if((a=fnd(pars,a))==(b=fnd(pars,b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

B con(I pars[],I a,I b){
  return fnd(pars,a)==fnd(pars,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m1,m2;cin>>n>>m1>>m2;
  fill_n(pars1,n,-1),fill_n(pars2,n,-1);
  for(I i=0;i<m1;i++){I u,v;cin>>u>>v,uni(pars1,u-1,v-1);}
  for(I i=0;i<m2;i++){I u,v;cin>>u>>v,uni(pars2,u-1,v-1);}
  for(I i=0;i<n;i++)for(I j=i+1;j<n;j++)
    if(!con(pars1,i,j)&&!con(pars2,i,j))
      ress.push_back({i,j}),uni(pars1,i,j),uni(pars2,i,j);
  printf("%i\n",ress.size());
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
  return 0;
}