#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1e5;
const I MAX=1e9;
const Lli MOD=1e9+7;

I csts[N];
vector<I>adjs1[N],adjs2[N];
B viss1[N],viss2[N];
vector<I>tops;
I pars[N];
I mins[N],cnts[N];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

void dfs1(I a){
  if(viss1[a])return;
  viss1[a]=true;
  for(auto b:adjs1[a])dfs1(b);
  tops.push_back(a);
}

void dfs2(I a){
  viss2[a]=true;
  for(auto b:adjs2[a])
    if(!viss2[b])dfs2(b),uni(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(pars,n,-1),fill_n(mins,n,MAX);
  for(I i=0;i<n;i++)cin>>csts[i];
  I m;cin>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs1[u].push_back(v);
    adjs2[v].push_back(u);
  }
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  for(auto i:tops)if(!viss2[i])dfs2(i);
  for(I i=0;i<n;i++){I j=fnd(i);mins[j]=min(mins[j],csts[i]);}
  for(I i=0;i<n;i++){I j=fnd(i);cnts[j]+=mins[j]==csts[i];}
  Lli com=1,cst=0;
  for(I i=0;i<n;i++){
    if(i!=fnd(i))continue;
    (com*=cnts[i])%=MOD;
    cst+=mins[i];
  }
  printf("%lli %lli\n",cst,com);
  return 0;
}