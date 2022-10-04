#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

map<I,vector<pair<I,I>>>adjs;
set<I>nods;
set<I>viss;
map<I,I>cons;
vector<pair<I,I>>unvs;
pair<I,I>edgs[N];
pair<I,I>outs[N];
I inds[N];
I pars[N];
vector<I>coms;
vector<tuple<I,I,I>>ress;

I dfs(I a,I i){
  if(viss.count(a))return 0;
  viss.insert(a);
  I cnt=1;
  for(auto[b,j]:adjs[a])cnt+=dfs(b,j);
  if(cnt==1)unvs.push_back({a,i});
  return cnt;
}

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

void add(I a,I i){
  if(cons.count(a))uni(cons[a],i);
  else cons[a]=i;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(pars,n,-1);
    adjs.clear(),nods.clear();
    viss.clear(),unvs.clear();
    coms.clear(),ress.clear();
    cons.clear();
    for(I i=0;i<n;i++){
      I x,y;cin>>x>>y;
      nods.insert(x);
      nods.insert(y);
      adjs[x].push_back({y,i});
      adjs[y].push_back({x,i});
      edgs[i]={x,y};
      add(x,i),add(y,i);
    }
    for(auto a:nods)dfs(a,-1);
    for(auto[a,i]:unvs)
      outs[fnd(i)]={a,i};
    for(I i=0;i<n;i++){
      auto[x,y]=edgs[i];
      I j=fnd(i);
      if(x!=outs[j].first)inds[j]=x;
      if(y!=outs[j].first)inds[j]=y;
    }
    for(I i=0;i<n;i++)if(i==fnd(i))
      coms.push_back(i);
    I a=-1;
    for(auto b:coms){
      if(a!=-1){
        auto[x,i]=outs[b];
        ress.push_back({i,x,inds[a]});
      }
      a=b;
    }
    printf("%i\n",ress.size());
    for(auto[w,a,b]:ress)
      printf("%i %i %i\n",w+1,a,b);
  }
}