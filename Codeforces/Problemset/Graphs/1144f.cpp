#include<iostream>
#include<cstdio>
#include<vector>
#include<tuple>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I M=2e5;

vector<tuple<I,I,B>>adjs1[N];
vector<I>adjs2[N];
pair<I,I>edgs[M];
B viss[N];
I ress[M];
I lens[N];
vector<I>tops;

void dfs1(I a,B c){
  if(viss[a])return;
  viss[a]=1;
  for(auto[b,i,d]:adjs1[a])
    ress[i]=d^c,dfs1(b,!c);
}

void dfs2(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs2[a])dfs2(b);
  tops.push_back(a);
}

I dfs3(I a){
  if(viss[a])return lens[a];
  viss[a]=1;
  I res=0;
  for(auto b:adjs2[a])
    res=max(res,dfs3(b));
  return lens[a]=res+1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs1[u].push_back({v,i,0});
    adjs1[v].push_back({u,i,1});
    edgs[i]={u,v};
  }
  dfs1(0,1);
  for(I i=0;i<m;i++){
    auto[u,v]=edgs[i];
    if(ress[i])swap(u,v);
    adjs2[u].push_back(v);
  }
  fill_n(viss,n,0);
  for(I i=0;i<n;i++)dfs2(i);
  reverse(tops.begin(),tops.end());
  fill_n(viss,n,0);
  B res=1;
  for(auto i:tops)res&=dfs3(i)-1<=1;
  if(!res){printf("NO\n");return 0;}
  printf("YES\n");
  for(I i=0;i<m;i++)printf("%i",ress[i]);
  return 0;
}