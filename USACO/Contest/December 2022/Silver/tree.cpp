#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
Lli h_arr[N];
vector<I>adjs1[N];
vector<pair<I,Lli>>adjs2[N];
B viss[N];
vector<I>tops;
vector<tuple<I,I,Lli>>ress;
Lli val;
Lli dfs1(I a,I p=-1){
  for(auto b:adjs1[a])if(b!=p){
    Lli cur=dfs1(b,a);
    h_arr[a]+=cur;
    if(cur>0)adjs2[b].push_back({a,cur});
    if(cur<0)adjs2[a].push_back({b,-cur});
  }
  return h_arr[a]-val;
}
void dfs2(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto[b,c]:adjs2[a])dfs2(b);
  tops.push_back(a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs1[u].push_back(v);
    adjs1[v].push_back(u);
  }
  val=accumulate(h_arr,h_arr+n,0ll)/n;
  dfs1(0);
  for(I i=0;i<n;i++)dfs2(i);
  reverse(tops.begin(),tops.end());
  for(I i=0;i<n;i++){
    I j=tops[i];
    for(auto[k,c]:adjs2[j])ress.push_back({j,k,c});
  }
  printf("%i\n",ress.size());
  for(auto[a,b,c]:ress)printf("%i %i %lli\n",a+1,b+1,c);
}