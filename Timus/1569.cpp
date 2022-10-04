#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;
const I M=10000;
const I MAX=1e9;

vector<I>adjs1[N],adjs2[N];
queue<I>que;
I diss[N];
I pars[N];
pair<I,I>edgs[M];
I dia;

void add(I d,I a,I p){
  if(d>=diss[a])return;
  diss[a]=d,pars[a]=p,que.push(a);
}

I dfs(I a){
  I res=1;
  for(auto b:adjs2[a]){
    I dis=dfs(b);
    dia=max(dia,res+dis);
    res=max(res,dis+1);
  }
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs1[a].push_back(b);
    adjs1[b].push_back(a);
    edgs[i]={a,b};
  }
  I res=MAX,x=-1,y=-1;
  for(I i=0;i<n;i++){
    fill_n(diss,n,MAX);
    for(I i=0;i<n;i++)adjs2[i].clear();
    add(0,i,-1);
    while(que.size()){
      I a=que.front();que.pop();
      for(auto b:adjs1[a])add(diss[a]+1,b,a);
    }
    for(I i=0;i<n;i++)if(pars[i]!=-1)
      adjs2[pars[i]].push_back(i);
    dia=0,dfs(i);
    if(dia<res)res=dia,x=i;
  }
  for(I i=0;i<m;i++){
    auto[a,b]=edgs[i];
    fill_n(diss,n,MAX);
    for(I i=0;i<n;i++)adjs2[i].clear();
    add(0,a,-1),add(0,b,a);
    while(que.size()){
      I a=que.front();que.pop();
      for(auto b:adjs1[a])add(diss[a]+1,b,a);
    }
    for(I i=0;i<n;i++)if(pars[i]!=-1)
      adjs2[pars[i]].push_back(i);
    dia=0,dfs(a);
    if(dia<res)res=dia,x=a,y=b;
  }
  fill_n(diss,n,MAX);
  for(I i=0;i<n;i++)adjs2[i].clear();
  add(0,x,-1);
  if(y!=-1)add(0,y,x);
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs1[a])add(diss[a]+1,b,a);
  }
  for(I i=0;i<n;i++)if(pars[i]!=-1)
    printf("%i %i\n",i+1,pars[i]+1);
}