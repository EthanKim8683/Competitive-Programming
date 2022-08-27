#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1000;

B a_arr[N];
B b_arr[N];
vector<I>adjs[N];
B viss[N];

void dfs(I a){
  if(viss[a])return;
  viss[a]=true;
  for(auto b:adjs[a])dfs(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,s;cin>>n>>s;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++){
    for(I j=i+1;j<n;j++)if(a_arr[i]&&a_arr[j])
      adjs[i].push_back(j);
    for(I j=0;j<i;j++)if(b_arr[i]&&b_arr[j])
      adjs[i].push_back(j);
  }
  dfs(0);
  if(viss[s-1])printf("YES\n");
  else printf("NO\n");
  return 0;
}