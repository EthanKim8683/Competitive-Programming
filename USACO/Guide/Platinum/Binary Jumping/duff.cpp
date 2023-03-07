#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I LOGN=17;
const I A=10;
vector<I>adjs[N];
set<I>pers[N];
I ancs[N][LOGN];
set<I>accs[N][LOGN];
set<I>ress;
I tbgs[N],teds[N];
I t=0;
void cmb(set<I>&a,set<I>&b){
  for(auto x:b){
    if(a.size()==A&&x>=*--a.end())return;
    a.insert(x);
    if(a.size()>A)a.erase(--a.end());
  }
}
void dfs(I a,I p){
  tbgs[a]=t++;
  ancs[a][0]=p;
  if(p!=a)cmb(accs[a][0],pers[p]);
  for(I i=1;i<LOGN;i++){
    I x=ancs[a][i-1],y=ancs[x][i-1];
    ancs[a][i]=y;
    cmb(accs[a][i],accs[a][i-1]);
    if(y!=x)cmb(accs[a][i],accs[x][i-1]);
  }
  for(auto b:adjs[a])if(b!=p)dfs(b,a);
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
void acc(I a,I b){
  if(a==b)return;
  cmb(ress,pers[a]);
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))cmb(ress,accs[a][i]),a=ancs[a][i];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,q;cin>>n>>m>>q;
  for(I i=0;i<n-1;i++){
    I v,u;cin>>v>>u,v--,u--;
    adjs[v].push_back(u);
    adjs[u].push_back(v);
  }
  for(I i=0;i<m;i++){
    I c;cin>>c,c--;
    if(pers[c].size()<A)pers[c].insert(i);
  }
  dfs(0,0);
  while(q--){
    I v,u,a;cin>>v>>u>>a,v--,u--;
    ress.clear();
    I c=lca(v,u);
    acc(v,c),acc(u,c),cmb(ress,pers[c]);
    while(ress.size()>a)ress.erase(--ress.end());
    printf("%i ",ress.size());
    for(auto x:ress)printf("%i ",x+1);
    printf("\n");
  }
}