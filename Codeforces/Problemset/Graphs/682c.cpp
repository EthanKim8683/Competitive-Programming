#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1e5;
const Lli MIN=-1e18;

I a_arr[N];
vector<pair<I,I>>adjs[N];
Lli diss[N],mins[N];
B viss[N];

void dfs1(I a){
  for(auto[b,c]:adjs[a]){
    diss[b]=diss[a]+c;
    mins[b]=min(mins[a],diss[b]);
    dfs1(b);
  }
}

void dfs2(I a){
  if(viss[a])return;
  viss[a]=true;
  for(auto[b,c]:adjs[a])dfs2(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=1;i<n;i++){
    I p,c;cin>>p>>c;
    adjs[p-1].push_back({i,c});
  }
  dfs1(0);
  for(I i=0;i<n;i++)
    if(diss[i]-mins[i]>a_arr[i])dfs2(i);
  I res=0;
  for(I i=0;i<n;i++)res+=viss[i];
  printf("%i\n",res);
  return 0;
}