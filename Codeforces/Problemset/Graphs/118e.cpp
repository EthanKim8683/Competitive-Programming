#include<iostream>
#include<cstdio>
#include<vector>
#include<set>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs[N];
set<pair<I,I>>viss2;
vector<pair<I,I>>ress;
B viss1[N];
I tbegs[N],tlows[N];
I t=0;
I cnt=0;

I dfs1(I a,I p=-1){
  if(viss1[a])return tlows[a];
  viss1[a]=1;
  tbegs[a]=tlows[a]=t++;
  for(auto b:adjs[a])if(b!=p){
    tlows[a]=min(tlows[a],dfs1(b,a));
    if(tlows[b]>tbegs[a])cnt++;
  }
  return tlows[a];
}

void dfs2(I a,I p=-1){
  if(viss1[a])return;
  viss1[a]=1;
  for(auto b:adjs[a])if(b!=p){
    if(viss2.find({a,b})==viss2.end()){
      viss2.insert({a,b});
      viss2.insert({b,a});
      ress.push_back({a,b});
      dfs2(b,a);
    }
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs1(0);
  if(cnt)printf("0\n"),exit(0);
  fill_n(viss1,n,0);
  dfs2(0);
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
}