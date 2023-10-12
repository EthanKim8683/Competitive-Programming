#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
const I C=1e9;
vector<pair<I,I>>adjs1[N],adjs2[N];
I c_arr[N];
vector<I>tops;
B viss[N];
vector<I>ress;
I n;
void dfs1(I a,I x){
  if(viss[a])return;
  viss[a]=1;
  for(auto[b,i]:adjs1[a])if(c_arr[i]>x)dfs1(b,x);
  tops.push_back(a);
}
I dfs2(I a,I x){
  if(viss[a])return 0;
  viss[a]=1;
  I res=1;
  for(auto[b,i]:adjs2[a])if(c_arr[i]>x)res+=dfs2(b,x);
  return res;
}
B chk(I x){
  fill_n(viss,n,0);
  tops.clear();
  for(I i=0;i<n;i++)dfs1(i,x);
  reverse(tops.begin(),tops.end());
  fill_n(viss,n,0);
  for(auto i:tops)if(dfs2(i,x)>1)return 0;
  return 1;
}
I fnd(){
  I l=0,r=C;
  while(l<r){
    I m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v,c;cin>>u>>v>>c,u--,v--;
    c_arr[i]=c;
    adjs1[u].push_back({v,i});
    adjs2[v].push_back({u,i});
  }
  I x=fnd();
  fill_n(viss,n,0);
  tops.clear();
  for(I i=0;i<n;i++)dfs1(i,x);
  reverse(tops.begin(),tops.end());
  fill_n(viss,n,0);
  for(auto i:tops){
    for(auto[j,k]:adjs2[i])if(c_arr[k]<=x&&!viss[j])ress.push_back(k);
    viss[i]=1;
  }
  printf("%i %i\n",x,ress.size());
  for(auto i:ress)printf("%i ",i+1);
}
/*
if we say all roads costing x or fewer traffic controllers are in the
optimal direction, then we only need to binary search until the graph
consisting of roads costing greater than x traffic controllers is acyclic

then, we can topologically sort the greater part and direct the cheaper
edges accordingly
*/