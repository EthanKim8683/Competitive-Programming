#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
I p_arr[N];
I h_arr[N];
vector<I>adjs[N];
Lli cnts[N],sums[N];
void dfs1(I a,I p=-1){
  cnts[a]=p_arr[a];
  sums[a]=0;
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    cnts[a]+=cnts[b];
    sums[a]+=h_arr[b];
  }
}
B dfs2(I a,I p=-1){
  B res=1;
  res&=sums[a]<=h_arr[a]+p_arr[a];
  res&=h_arr[a]>=-cnts[a];
  res&=h_arr[a]<=cnts[a];
  res&=(h_arr[a]+cnts[a])%2==0;
  for(auto b:adjs[a])if(b!=p)res&=dfs2(b,a);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>p_arr[i];
    for(I i=0;i<n;i++)cin>>h_arr[i];
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I x,y;cin>>x>>y,x--,y--;
      adjs[x].push_back(y);
      adjs[y].push_back(x);
    }
    dfs1(0);
    printf("%s\n",dfs2(0)?"YES":"NO");
  }
}