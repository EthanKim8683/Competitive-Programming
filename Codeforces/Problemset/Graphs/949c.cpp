#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<unordered_set>
 
using namespace std;
 
using I=int;
using B=bool;
 
const I N=100000;
const I MAX=1e9;
 
I u_arr[N];
vector<I>adjs1[N],adjs2[N];
B viss1[N],viss2[N];
vector<I>tops;
vector<I>sccs[N];
I pars[N];
I n;

void dfs1(I a){
  if(viss1[a])return;
  viss1[a]=true;
  for(auto b:adjs1[a])dfs1(b);
  tops.push_back(a);
}

void dfs2(I a,I r){
  if(viss2[a])return;
  viss2[a]=true;
  sccs[r].push_back(a);
  for(auto b:adjs2[a])dfs2(b,r);
}

void scc(){
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  for(auto i:tops)if(!viss2[i])dfs2(i,i);
}

void add(I i,I j){
  adjs1[i].push_back(j);
  adjs2[j].push_back(i);
}
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m,h;cin>>n>>m>>h;
  for(I i=0;i<n;i++)cin>>u_arr[i];
  for(I i=0;i<m;i++){
    I c1,c2;cin>>c1>>c2,c1--,c2--;
    I u1=u_arr[c1],u2=u_arr[c2];
    if((u1+1)%h==u2)add(c1,c2);
    if((u2+1)%h==u1)add(c2,c1);
  }
  scc();
  for(I i=0;i<n;i++)for(auto j:sccs[i])pars[j]=i;
  I r=-1;
  for(I i=0;i<n;i++){
    if(pars[i]!=i)continue;
    B vld=1;
    for(auto j:sccs[i])for(auto k:adjs1[j])
      vld&=pars[j]==pars[k];
    if(!vld)continue;
    if(r==-1||sccs[i].size()<sccs[r].size())r=i;
  }
  printf("%i\n",sccs[r].size());
  for(auto i:sccs[r])printf("%i ",i+1);
  return 0;
}