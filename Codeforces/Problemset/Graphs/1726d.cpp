#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I M=N+2;

vector<pair<I,I>>adjs[N];
I ress[M];
B viss[N];
I deps[N];
pair<I,I>edgs[M];
I pars[N];
map<I,I>cnts;

void dfs(I a){
  viss[a]=1;
  for(auto[b,i]:adjs[a]){
    if(viss[b])continue;
    ress[i]=1;
    pars[b]=a;
    deps[b]=deps[a]+1;
    dfs(b);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(viss,n,0),fill_n(ress,m,0);
    fill_n(pars,n,-1),fill_n(deps,n,0);
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<m;i++){
      I a,b;cin>>a>>b,a--,b--;
      adjs[a].push_back({b,i});
      adjs[b].push_back({a,i});
      edgs[i]={a,b};
    }
    dfs(0);
    cnts.clear();
    for(I i=0;i<m;i++){
      if(ress[i])continue;
      auto[a,b]=edgs[i];
      cnts[a]++,cnts[b]++;
    }
    if(cnts.size()==3){
      I r=-1;
      B vld=1;
      for(auto[a,cnt]:cnts){
        vld&=cnt==2;
        if(r==-1||deps[a]>deps[r])r=a;
      }
      if(vld){
        I x,y;
        for(auto[b,i]:adjs[r]){
          if(!ress[i])x=i;
          else if(pars[r]==b)y=i;
        }
        ress[x]=1;
        ress[y]=0;
      }
    }
    for(I i=0;i<m;i++)printf("%i",ress[i]);
    printf("\n");
  }
}