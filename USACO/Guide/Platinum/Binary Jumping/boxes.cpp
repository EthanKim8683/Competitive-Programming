#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I LOGN=17;
#ifndef ETHANKIM8683
#include"grader.h"
#else
vector<I>_adjs[N];
I _ancs[N][LOGN];
I _tbgs[N],_teds[N];
pair<I,I>_poss[N];
vector<tuple<I,I,I,I>>_boxs;
vector<I>_unis;
vector<I>_tars;
I _t=0;
I _n,_q;
void _dfs(I a,I p){
  _tbgs[a]=_t++;
  _ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)_ancs[a][i]=_ancs[_ancs[a][i-1]][i-1];
  for(auto b:_adjs[a])if(b!=p)_dfs(b,a);
  _teds[a]=_t;
}
B _anc(I a,I b){
  return _tbgs[a]<=_tbgs[b]&&_teds[a]>=_teds[b];
}
I _lca(I a,I b){
  if(_anc(a,b))return a;
  if(_anc(b,a))return b;
  for(I i=LOGN-1;i>=0;i--)if(!_anc(_ancs[a][i],b))a=_ancs[a][i];
  return _ancs[a][0];
}
B _ins(pair<I,I>pos,tuple<I,I,I,I>box){
  auto[x,y]=pos;
  auto[x1,y1,x2,y2]=box;
  return x1<=x&&x<=x2&&y1<=y&&y<=y2;
}
I _cnt(pair<I,I>pos){
  I res=0;
  for(auto box:_boxs)res+=_ins(pos,box);
  return res;
}
I getN(){
  return _n;
}
I getQ(){
  return _q;
}
void setFarmLocation(I i,I x,I y){
  assert(0<=i&&i<=_n-1);
  assert(1<=x&&x<=_n&&1<=y&&y<=_n);
  _poss[i]={x,y};
}
void addBox(I x1,I y1,I x2,I y2){
  assert(1<=x1&&x1<=x2&&x2<=_n);
  assert(1<=y1&&y1<=y2&&y2<=_n);
  _boxs.push_back({x1,y1,x2,y2});
}
#endif
vector<I>adjs[N];
I sizs[N];
pair<I,I>poss[N];
I ancs[N][LOGN];
I deps[N];
I tbgs[N],teds[N];
I y=1;
I t=0;
I dfs1(I a,I p,I d=0){
  tbgs[a]=t++;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  deps[a]=d;
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p)sizs[a]+=dfs1(b,a,d+1);
  teds[a]=t;
  return sizs[a];
}
void dfs2(I a,I p,I x=1){
  poss[a]={x,y++};
  x+=sizs[a];
  for(auto b:adjs[a])if(b!=p){
    x-=sizs[b];
    dfs2(b,a,x);
  }
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
void addRoad(I a,I b){
  adjs[a].push_back(b);
  adjs[b].push_back(a);
}
void buildFarms(){
  I n=getN();
  dfs1(0,0),dfs2(0,0);
  for(I i=0;i<n;i++){
    auto[x,y]=poss[i];
    setFarmLocation(i,x,y);
  }
}
void notifyFJ(I a,I b){
  if(anc(a,b)){
    auto[x1,y1]=poss[a];
    auto[x2,y2]=poss[b];
    addBox(x1,y1,x2,y2);
    return;
  }
  if(anc(b,a)){
    auto[x1,y1]=poss[b];
    auto[x2,y2]=poss[a];
    addBox(x1,y1,x2,y2);
    return;
  }
  I c=a;
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[c][i],b))c=ancs[c][i];
  auto[x1,y1]=poss[c];
  auto[x2,y2]=poss[ancs[c][0]];
  auto[x3,y3]=poss[a];
  auto[x4,y4]=poss[b];
  addBox(x1,y1,x3,y3);
  addBox(x2,y2,x4,y4);
}
#ifdef ETHANKIM8683
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>_n>>_q;
  for(I i=0;i<_n-1;i++){
    I a,b;cin>>a>>b;
    addRoad(a,b);
    _adjs[a].push_back(b);
    _adjs[b].push_back(a);
  }
  _dfs(0,0);
  fill_n(_poss,_n,pair<I,I>{-1,-1});
  buildFarms();
  B all=1;
  for(I i=0;i<_n;i++)all&=_poss[i]!=pair<I,I>{-1,-1};
  assert(all);
  for(I i=0;i<_q;i++){
    I a,b;cin>>a>>b;
    _boxs.clear();
    notifyFJ(a,b);
    _unis.clear();
    for(I j=0;j<_n;j++){
      I cnt=_cnt(_poss[j]);
      assert(cnt<=1);
      if(cnt==1)_unis.push_back(j);
    }
    _tars.clear();
    I c=_lca(a,b);
    for(I j=a;j!=c;j=_ancs[j][0])_tars.push_back(j);
    for(I j=b;j!=c;j=_ancs[j][0])_tars.push_back(j);
    _tars.push_back(c);
    sort(_tars.begin(),_tars.end());
    assert(_unis.size()==_tars.size());
    for(I j=0;j<_unis.size();j++){
      assert(_unis[j]==_tars[j]);
    }
  }
}
#endif