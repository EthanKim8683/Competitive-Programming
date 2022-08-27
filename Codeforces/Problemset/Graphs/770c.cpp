#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I K=N;

I cous[K];
B uses[N];
B viss[N];
I invs[N];
vector<I>outs[N],inds[N];
vector<I>tops;

void dfs1(I a){
  if(uses[a])return;
  uses[a]=true;
  for(auto b:inds[a])dfs1(b);
}

void dfs2(I a){
  if(!uses[a]||viss[a])return;
  viss[a]=true;
  for(auto b:outs[a])dfs2(b);
  tops.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<k;i++){I x;cin>>x,cous[i]=x-1;}
  for(I i=0;i<n;i++){
    I t;cin>>t;
    for(I j=0;j<t;j++){
      I k;cin>>k,k--;
      outs[k].push_back(i);
      inds[i].push_back(k);
    }
  }
  for(I i=0;i<k;i++)dfs1(cous[i]);
  for(I i=0;i<n;i++)dfs2(i);
  reverse(tops.begin(),tops.end());
  for(I i=0;i<tops.size();i++)invs[tops[i]]=i;
  for(auto i:tops)for(auto j:inds[i])
    if(invs[j]>invs[i]){printf("-1\n");return 0;}
  printf("%i\n",tops.size());
  for(auto v:tops)printf("%i ",v+1);
  return 0;
}