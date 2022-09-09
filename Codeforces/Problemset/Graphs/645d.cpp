#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

using I=int;
using B=bool;

const I N=100000;
const I M=100000;

vector<I>adjs[N];
vector<I>tops;
map<pair<I,I>,I>edgs;
B viss[N];
I n,m;

void dfs(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs(b);
  tops.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[v].push_back(u);
    edgs[{v,u}]=i;
  }
  for(I i=0;i<n;i++)dfs(i);
  reverse(tops.begin(),tops.end());
  I res=0;
  for(I i=0;i+1<n;i++){
    auto it=edgs.find({tops[i],tops[i+1]});
    if(it==edgs.end()){printf("-1\n");return 0;}
    res=max(res,it->second+1);
  }
  printf("%i\n",res);
  return 0;
}