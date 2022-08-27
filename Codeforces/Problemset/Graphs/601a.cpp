#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

using I=int;
using B=bool;

const I N=400;
const I MAX=1e9;

vector<I>adjs[2][N];
vector<pair<I,I>>uses;
I dsts[N];
queue<I>que;

B fnd(I i,I j){
  if(i>j)swap(i,j);
  return find(uses.begin(),uses.end(),pair<I,I>(i,j))!=uses.end();
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(dsts,n,MAX);
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[0][u].push_back(v);
    adjs[0][v].push_back(u);
    uses.push_back({min(u,v),max(u,v)});
  }
  I c=0;
  if(fnd(0,n-1)){
    c=1;
    for(I i=0;i<n;i++)for(I j=i+1;j<n;j++){
      if(fnd(i,j))continue;
      adjs[1][i].push_back(j);
      adjs[1][j].push_back(i);
    }
  }
  dsts[0]=0;
  que.push(0);
  while(que.size()){
    auto a=que.front();que.pop();
    I d=dsts[a];
    for(auto b:adjs[c][a]){
      if(d+1>=dsts[b])continue;
      dsts[b]=d+1;
      que.push(b);
    }
  }
  if(dsts[n-1]==MAX)printf("-1\n");
  else printf("%i\n",dsts[n-1]);
  return 0;
}