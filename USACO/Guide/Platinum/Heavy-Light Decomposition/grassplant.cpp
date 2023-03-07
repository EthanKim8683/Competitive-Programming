#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=100000;
vector<I>adjs[N];
I sizs[N],inds[N],tops[N],deps[N],pars[N];
I segs[2*N];
map<pair<I,I>,I>nods;
I n;
I ind=0;
void upd(I l,I r){
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)segs[l++]++;
    if(r&1)segs[--r]++;
  }
}
I qry(I i){
  I res=0;
  for(i+=n;i>0;i>>=1)res+=segs[i];
  return res;
}
void dfs1(I a,I p){
  sizs[a]=1;
  pars[a]=p;
  for(auto&b:adjs[a])if(b!=p){
    deps[b]=deps[a]+1;
    dfs1(b,a);
    sizs[a]+=sizs[b];
    if(sizs[b]>sizs[adjs[a][0]])swap(b,adjs[a][0]);
  }
}
void dfs2(I a,I p=-1){
  inds[a]=ind++;
  for(auto b:adjs[a])if(b!=p){
    tops[b]=b==adjs[a][0]?tops[a]:b;
    dfs2(b,a);
    nods[{a,b}]=nods[{b,a}]=b;
  }
}
void pat(I a,I b){
  while(tops[a]!=tops[b]){
    if(deps[tops[a]]<deps[tops[b]])swap(a,b);
    upd(inds[tops[a]],inds[a]+1);
    a=pars[tops[a]];
  }
  if(deps[a]>deps[b])swap(a,b);
  upd(inds[a]+1,inds[b]+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs1(0,0),dfs2(0);
  while(m--){
    C t;cin>>t;
    if(t=='P'){
      I a,b;cin>>a>>b,a--,b--;
      pat(a,b);
    }
    if(t=='Q'){
      I a,b;cin>>a>>b,a--,b--;
      printf("%i\n",qry(inds[nods[{a,b}]]));
    }
  }
}