#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I LOGN=17;
const I MAX=1e9;
I pars[N];
pair<I,I>ancs[N][LOGN];
I spas[N][LOGN];
I n,m;
I fnd(I a){
  if(pars[a]<0)return a;
  return pars[a]=fnd(pars[a]);
}
void uni(I t,I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  ancs[b][0]={a,t},pars[a]+=pars[b],pars[b]=a;
}
void bld1(){
  for(I i=1;i<LOGN;i++)for(I j=0;j<n;j++){
    auto[k,t]=ancs[j][i-1];
    ancs[j][i]=ancs[k][i-1];
  }
}
I anc(I a,I t1){
  for(I i=LOGN-1;i>=0;i--){
    auto[b,t2]=ancs[a][i];
    if(t2<=t1)a=b;
  }
  return a;
}
I qry1(I a,I b){
  I l=-1,r=m-1;
  while(l<r){
    I t=l+(r-l)/2;
    anc(a,t)==anc(b,t)?r=t:l=t+1;
  }
  return l+1;
}
void bld2(){
  for(I i=0;i<n-1;i++)spas[i][0]=qry1(i,i+1);
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n-1;j++)spas[j][i]=max(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
I qry2(I l,I r){
  if(l==r)return 0;
  I d=31-__builtin_clz(r-l);
  return max(spas[l][d],spas[r-(1<<d)][d]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I q;cin>>n>>m>>q;
    fill_n(pars,n,-1);
    for(I i=0;i<n;i++)ancs[i][0]={i,MAX};
    for(I i=0;i<m;i++){
      I u,v;cin>>u>>v,u--,v--;
      uni(i,u,v);
    }
    bld1(),bld2();
    while(q--){
      I l,r;cin>>l>>r,l--;
      printf("%i ",max(qry2(l,r-1),0));
    }
    printf("\n");
  }
}
/*
we can use DSU and binary lifting to find the earliest point in which two
vertices are connected

then, we can find, for every vertex v, the earliest point in which it's
connected with its neighbor v + 1

the logic here is that, if all v is connected with v + 1 by time t in range
[l, r - 1), then all vertices in [l, r - 1) are connected by time t

this allows us to perform range maximum queries easily
*/