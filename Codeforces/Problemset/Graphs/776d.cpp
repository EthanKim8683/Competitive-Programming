#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<pair<I,B>>adjs[N];
I r_arr[N];
vector<I>cons[N];
B viss[N];
B cols[N];

B dfs(I a,B col){
  if(viss[a])return cols[a]==col;
  viss[a]=1;
  cols[a]=col;
  for(auto[b,c]:adjs[a])
    if(!dfs(b,(col^c)==0))return 0;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>r_arr[i];
  for(I i=0;i<m;i++){
    I x;cin>>x;
    for(I j=0;j<x;j++){
      I y;cin>>y;
      cons[y-1].push_back(i);
    }
  }
  for(I i=0;i<n;i++){
    I a=cons[i][0],b=cons[i][1];
    adjs[a].push_back({b,r_arr[i]});
    adjs[b].push_back({a,r_arr[i]});
  }
  for(I i=0;i<m;i++)if(!dfs(i,cols[i]))
    printf("NO\n"),exit(0);
  printf("YES\n");
  return 0;
}