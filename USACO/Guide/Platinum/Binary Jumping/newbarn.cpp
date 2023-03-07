#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I Q=1e5;
const I N=1e5;
const I LOGN=17;
pair<C,I>qrys[Q];
vector<I>adjs[N];
vector<I>rots;
I deps[N];
I ancs[N][LOGN];
I tbgs[N],teds[N];
I pars[N];
pair<I,I>dias[N];
I t=0;
void dfs(I a,I p,I d=0){
  tbgs[a]=t++;
  deps[a]=d;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])dfs(b,a,d+1);
  teds[a]=t;
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return ancs[a][0];
}
I dis(I a,I b){
  return deps[a]+deps[b]-2*deps[lca(a,b)];
}
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
I main(){
#ifndef ETHANKIM8683
  freopen("newbarn.in","r",stdin);
  freopen("newbarn.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  for(I i=0;i<q;i++){
    C t;cin>>t;
    if(t=='B'){
      I p;cin>>p;
      qrys[i]={'B',p-1};
    }
    if(t=='Q'){
      I k;cin>>k;
      qrys[i]={'Q',k-1};
    }
  }
  I n=0;
  for(I i=0;i<q;i++){
    auto[t,p]=qrys[i];
    if(t!='B')continue;
    (p<0?rots:adjs[p]).push_back(n++);
  }
  for(auto a:rots)dfs(a,a);
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++)dias[i]={i,i};
  n=0;
  for(I i=0;i<q;i++){
    auto[t,x]=qrys[i];
    if(t=='B'){
      I j=n++;
      if(x<0)continue;
      pars[j]=x=fnd(x);
      auto[a,b]=dias[x];
      I d1=dis(a,j),d2=dis(b,j),d3=dis(a,b);
      if(d1>d3)dias[x]={a,j};
      if(d2>d3)dias[x]={b,j};
    }
    if(t=='Q'){
      auto[a,b]=dias[fnd(x)];
      printf("%i\n",max(dis(a,x),dis(b,x)));
    }
  }
}