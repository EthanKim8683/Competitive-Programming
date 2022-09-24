#include<iostream>
#include<cstdio>
#include<map>
#include<algorithm>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1e5;

map<S,I>cpss;
I pars[N<<1];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

B con(I a,I b){
  return fnd(a)==fnd(b);
}

I qry(I a,I b){
  if(con(a<<1,b<<1)||con(a<<1|1,b<<1|1))return 1;
  if(con(a<<1,b<<1|1)||con(a<<1|1,b<<1))return 2;
  return 3;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,q;cin>>n>>m>>q;
  fill_n(pars,n<<1,-1);
  for(I i=0;i<n;i++){S a;cin>>a;cpss[a]=i;}
  for(I i=0;i<m;i++){
    I t;S x,y;cin>>t>>x>>y;
    I a=cpss[x],b=cpss[y];
    if(t==1){
      if(qry(a,b)==2){printf("NO\n");continue;}
      printf("YES\n");
      uni(a<<1,b<<1),uni(a<<1|1,b<<1|1);
    }else{
      if(qry(a,b)==1){printf("NO\n");continue;}
      printf("YES\n");
      uni(a<<1,b<<1|1),uni(a<<1|1,b<<1);
    }
  }
  for(I i=0;i<q;i++){
    S x,y;cin>>x>>y;
    printf("%i\n",qry(cpss[x],cpss[y]));
  }
  return 0;
}