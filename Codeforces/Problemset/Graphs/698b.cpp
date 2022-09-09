#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=200000;

I a_arr[N];
vector<I>adjs[N];
B viss[N];
vector<I>tops;
vector<I>pars;

void dfs1(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs1(b);
  tops.push_back(a);
}

void dfs2(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs2(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<n;i++)adjs[a_arr[i]].push_back(i);
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  fill_n(viss,n,0);
  I r=-1;
  for(auto i:tops){
    if(viss[i])continue;
    dfs2(i);
    pars.push_back(i);
    if(r==-1||a_arr[i]==i)r=i;
  }
  I res=0;
  if(a_arr[r]!=r)
    a_arr[r]=r,res++;
  for(I i=0;i<pars.size();i++)
    if(pars[i]!=r)a_arr[pars[i]]=r,res++;
  printf("%i\n",res);
  for(I i=0;i<n;i++)printf("%i ",a_arr[i]+1);
  return 0;
}