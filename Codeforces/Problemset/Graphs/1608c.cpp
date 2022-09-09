#include<iostream>
#include<cstdio>
#include<numeric>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I a_arr[N],b_arr[N];
I inds1[N],inds2[N];
B viss1[N],viss2[N];
vector<I>adjs[N];

B cmp1(I a,I b){
  return a_arr[a]<a_arr[b];
}

B cmp2(I a,I b){
  return b_arr[a]<b_arr[b];
}

void dfs1(I a){
  if(viss1[a])return;
  viss1[a]=1;
  for(auto b:adjs[a])dfs1(b);
}

void dfs2(I a){
  if(viss2[a])return;
  viss2[a]=1;
  for(auto b:adjs[a])dfs2(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(viss1,n,0),fill_n(viss2,n,0);
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    iota(inds1,inds1+n,0),iota(inds2,inds2+n,0);
    sort(inds1,inds1+n,cmp1),sort(inds2,inds2+n,cmp2);
    for(I i=0;i+1<n;i++){
      adjs[inds1[i]].push_back(inds1[i+1]);
      adjs[inds2[i]].push_back(inds2[i+1]);
    }
    dfs1(inds1[n-1]),dfs2(inds2[n-1]);
    for(I i=0;i<n;i++)printf("%i",viss1[i]&&viss2[i]);
    printf("\n");
  }
  return 0;
}