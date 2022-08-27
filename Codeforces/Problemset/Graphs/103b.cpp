#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=100;

I pars[N];
I cnt;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

B uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return false;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  cnt--;
  return true;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  cnt=n;
  fill_n(pars,n,-1);
  B cyc=false;
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y;
    if(!uni(x-1,y-1)){
      if(cyc){printf("NO\n");return 0;}
      cyc=true;
    }
  }
  if(cyc&&cnt==1)printf("FHTAGN!\n");
  else printf("NO\n");
  return 0;
}