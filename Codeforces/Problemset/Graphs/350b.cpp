#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

B typs[N];
B viss[N];
vector<I>adjs[N];
I lens[N];
vector<I>stks;
I dep=1;
I len=0;

I dfs1(I a){
  if(viss[a])return lens[a];
  viss[a]=true;
  lens[a]=typs[a];
  for(auto b:adjs[a]){
    I l=dfs1(b);
    if(l)lens[a]=max(lens[a],l+1);
  }
  return lens[a];
}

B dfs2(I a){
  if(dep==len){
    for(auto i:stks)printf("%i ",i+1);
    printf("%i",a+1);
    return true;
  }
  dep++;
  stks.push_back(a);
  for(auto b:adjs[a])if(dfs2(b))return true;
  stks.pop_back();
  dep--;
  return false;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>typs[i];
  for(I i=0;i<n;i++){
    I a;cin>>a;
    if(a)adjs[a-1].push_back(i);
  }
  for(I i=0;i<n;i++)
    if(typs[i]||adjs[i].size()>1)
      adjs[i].clear();
  I r=-1;
  for(I i=0;i<n;i++){
    dfs1(i);
    if(r==-1||lens[i]>lens[r])r=i;
  }
  len=lens[r];
  printf("%i\n",len);
  dfs2(r);
  return 0;
}