#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

vector<I>adjs1[N];
vector<I>adjs2[N];
vector<I>tops;
vector<pair<I,I>>ress;
I invs[N];
B viss[N];

void dfs1(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs1[a])dfs1(b);
  tops.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(viss,n,0);
    tops.clear(),ress.clear();
    for(I i=0;i<n;i++)adjs1[i].clear(),adjs2[i].clear();
    for(I i=0;i<m;i++){
      I t,x,y;cin>>t>>x>>y,x--,y--;
      if(t)adjs1[x].push_back(y);
      else adjs2[x].push_back(y),adjs2[y].push_back(x);
    }
    for(I i=0;i<n;i++)dfs1(i);
    reverse(tops.begin(),tops.end());
    for(I i=0;i<n;i++)invs[tops[i]]=i;
    B vld=1;
    for(auto i:tops)for(auto j:adjs1[i])vld&=invs[j]>invs[i];
    if(!vld){printf("NO\n");continue;}
    for(auto i:tops)for(auto j:adjs1[i])
      ress.push_back({i,j});
    for(auto i:tops)for(auto j:adjs2[i])if(invs[j]>invs[i])
      ress.push_back({i,j});
    printf("YES\n");
    for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
  }
  return 0;
}