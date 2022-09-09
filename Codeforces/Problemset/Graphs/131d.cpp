#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=3000;
const I MAX=1e9;

vector<I>adjs[N];
I viss[N];
I diss[N];
queue<I>que;

void add(I i,I d){
  if(d>=diss[i])return;
  diss[i]=d;
  que.push(i);
}

B dfs(I a,I r,I p=-1){
  if(viss[a])return false;
  viss[a]=true;
  B res=false;
  for(auto b:adjs[a]){
    if(b==p)continue;
    if(b==r)res=true;
    res|=dfs(b,r,a);
  }
  if(res)add(a,0);
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(diss,n,MAX);
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for(I i=0;i<n;i++){
    fill_n(viss,n,false);
    if(dfs(i,i))break;
  }
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs[a])add(b,diss[a]+1);
  }
  for(I i=0;i<n;i++)printf("%i ",diss[i]);
  return 0;
}