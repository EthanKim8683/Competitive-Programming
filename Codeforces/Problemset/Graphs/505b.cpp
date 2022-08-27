#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=100;
const I M=100;

I pars[M][N];

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
  I n,m;cin>>n>>m;
  fill(&pars[0][0],&pars[0][0]+sizeof(pars)/sizeof(I),-1);
  for(I i=0;i<m;i++){
    I a,b,c;cin>>a>>b>>c,a--,b--,c--;
    uni(pars[c],a,b);
  }
  I q;cin>>q;
  while(q--){
    I u,v;cin>>u>>v,u--,v--;
    I res=0;
    for(I i=0;i<m;i++)res+=con(pars[i],u,v);
    printf("%i\n",res);
  }
  return 0;
}